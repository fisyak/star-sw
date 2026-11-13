// Offline behavioral tests of the actual Jenkinsfile helpers. Only Jenkins IO is replaced.
// java -cp groovy-all-2.4.21.jar groovy.ui.GroovyMain tests/ci/test_reviewer_reminders.groovy
import groovy.json.JsonOutput
import groovy.json.JsonSlurperClassic

def loader = new GroovyClassLoader()
loader.parseClass('package com.cloudbees.groovy.cps; @interface NonCPS {}')
def source = new File(args ? args[0] : 'Jenkinsfile.reminders').text
def now = java.time.Instant.parse('2026-10-21T13:00:00Z').toEpochMilli()
def base = 'https://git.example.test/gitea'
def repo = '/repos/STAR/star-sw'
def pull = { Map changes = [:] ->
  [number: 1, state: 'open', merged: false, draft: false,
   title: 'Fix detector calibration', user: [login: 'author'],
   created_at: '2026-10-16T13:00:00Z',
   requested_reviewers: [[login: 'alice'], [login: 'bob']]] + changes
}
def review = { Map changes = [:] ->
  [id: 1, state: 'REQUEST_REVIEW', dismissed: false, user: [login: 'alice'],
   team: null, submitted_at: '2026-10-19T13:00:00Z'] + changes
}
int passed = 0
def test = { String name, Closure body ->
  def routes = [:]
  def calls = []
  def mails = []
  def logs = []
  def warnings = []
  def route = { String path, Object data, int page = 0, Map headers = [:], int status = 200 ->
    routes[[path, page]] = [status: status, content: JsonOutput.toJson(data), headers: headers]
  }
  route(repo + '/pulls', [pull()], 1)
  route(repo + '/pulls/1', pull())
  route(repo + '/pulls/1/reviews', [review()], 1)
  ['alice', 'bob', 'carol'].each { route('/users/' + it, [email: it + '@example.test']) }
  def binding = new Binding([
    env: [GITEA_TOKEN: 'test-secret', GITEA_BASE_URL: base, GITEA_REPOSITORY: 'STAR/star-sw'],
    params: [DRY_RUN: true, MIN_AGE_HOURS: '24', GITEA_CREDENTIALS_ID: 'test', REVIEWER_HANDLES: ''],
    pipeline: { Closure ignored -> },
    httpRequest: { Map options ->
      calls << options
      assert options.keySet() == ['url', 'httpMode', 'customHeaders', 'timeout',
        'quiet', 'consoleLogResponseBody', 'validResponseCodes'] as Set
      assert options.httpMode == 'GET'
      assert options.quiet && !options.consoleLogResponseBody
      assert options.timeout == 30
      assert options.customHeaders.find { it.name == 'Authorization' } ==
        [name: 'Authorization', value: 'token test-secret', maskValue: true]
      assert !options.url.contains('test-secret')
      def uri = new URI(options.url)
      def query = uri.query?.split('&')?.collectEntries { it.split('=', 2) as List } ?: [:]
      int page = (query.page ?: '0') as int
      def path = uri.path.substring('/gitea/api/v1'.length())
      def response = routes[[path, page]]
      if (response == null && page > 1) return [status: 200, content: '[]', headers: [:]]
      assert response != null: "Unexpected request ${path}, page ${page}"
      return response
    },
    error: { String message -> throw new IllegalArgumentException(message) },
    echo: { String message -> logs << message },
    unstable: { String message -> warnings << message },
    mail: { Map message -> mails << message },
    usernamePassword: { Map options -> options },
    withCredentials: { List credentials, Closure action -> action() }
  ])
  def script = new GroovyShell(loader, binding).parse(source)
  script.run()
  def collect = { Map options = [:] ->
    script.collectReminders(base, 'STAR/star-sw', options.age ?: '24',
      options.reviewers ?: '', now)
  }
  def fails = { Closure action ->
    try { action(); assert false: 'Expected validation failure' }
    catch (Exception expected) { assert !expected.message.contains('test-secret') }
  }
  body([script: script, route: route, report: collect, fails: fails,
        calls: calls, mails: mails, logs: logs, warnings: warnings, binding: binding])
  println "PASS ${name}"
  passed++
}

test('only outstanding reviewers receive their own digest') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob'], state: 'APPROVED')], 1)
  def messages = t.report().messages
  assert messages*.handle == ['alice']
  assert messages[0].to == 'alice@example.test'
  assert messages[0].body.contains(base + '/STAR/star-sw/pulls/1')
  assert messages[0].pr_numbers == [1]
}
test('multiple PRs group per reviewer and sort by PR number') { t ->
  t.route(repo + '/pulls', [pull(number: 2), pull(), pull(number: 3)], 1)
  [2, 3].each { n ->
    t.route(repo + '/pulls/' + n, pull(number: n))
    t.route(repo + '/pulls/' + n + '/reviews', [review(user: [login: n == 2 ? 'alice' : 'bob'])], 1)
  }
  assert t.report().messages*.pr_numbers == [[1, 2], [3]]
}
test('short pages continue and duplicate PR summaries are deduplicated') { t ->
  t.route(repo + '/pulls', [pull(), pull(number: 2)], 2)
  t.route(repo + '/pulls/2', pull(number: 2))
  t.route(repo + '/pulls/2/reviews', [review(state: 'APPROVED')], 1)
  t.route(repo + '/pulls/2/reviews', [review(id: 2, submitted_at: '2026-10-20T12:00:00Z')], 2)
  assert t.report().messages[0].pr_numbers == [1, 2]
}
test('empty review pages with next links continue without following remote URLs') { t ->
  t.route(repo + '/pulls/1/reviews', [], 1, [Link: ['<https://evil.test/>; rel="next"']])
  t.route(repo + '/pulls/1/reviews', [review()], 2)
  assert t.report().messages.size() == 1
  assert t.calls.every { it.url.startsWith(base + '/api/v1/') }
}
test('repeated pages fail before any delivery') { t ->
  t.route(repo + '/pulls', [pull()], 2)
  t.fails { t.report() }
  assert !t.mails
}
['APPROVED', 'REQUEST_CHANGES', 'REJECTED', 'COMMENT', 'PENDING'].each { state ->
  test("${state} alone does not trigger reminders") { t ->
    t.route(repo + '/pulls/1/reviews', [review(state: state)], 1)
    assert !t.report().messages
  }
}
test('dismissed requests do not trigger reminders') { t ->
  t.route(repo + '/pulls/1/reviews', [review(dismissed: true)], 1)
  assert !t.report().messages
}
test('latest completed review wins regardless of API order') { t ->
  t.route(repo + '/pulls/1/reviews', [review(id: 2, state: 'APPROVED', submitted_at: '2026-10-20T12:00:00Z'), review()], 1)
  assert !t.report().messages
}
test('new requests after approval and unpublished drafts preserve requests') { t ->
  t.route(repo + '/pulls/1/reviews', [review(id: 2),
    review(id: 1, state: 'APPROVED', submitted_at: '2026-10-17T13:00:00Z'),
    review(id: 3, state: 'PENDING', submitted_at: '2026-10-21T12:00:00Z')], 1)
  assert t.report().messages.size() == 1
}
test('recent requests and renewed requests wait for the threshold') { t ->
  [[submitted_at: '2026-10-21T12:00:00Z'], [updated_at: '2026-10-21T12:00:00Z']].each { fields ->
    t.route(repo + '/pulls/1/reviews', [review(fields)], 1)
    assert !t.report().messages
  }
}
test('exact age boundary and timestamp offsets are supported') { t ->
  t.route(repo + '/pulls/1/reviews', [review(submitted_at: '2026-10-20T09:00:00-04:00')], 1)
  assert t.report().messages.size() == 1
}
test('closed merged draft WIP young and unassigned PRs are skipped') { t ->
  [[state: 'closed'], [merged: true], [draft: true], [title: 'WIP: fix'],
   [title: '[WIP] fix'], [title: ' Draft: fix'], [created_at: '2026-10-21T12:00:00Z']].each { fields ->
    t.route(repo + '/pulls/1', pull(fields))
    assert !t.report().messages
  }
  t.route(repo + '/pulls/1', pull())
  t.route(repo + '/pulls/1/reviews', [], 1)
  assert !t.report().messages
}
test('team expansion paginates deduplicates and skips author and completed members') { t ->
  t.route(repo + '/pulls/1/reviews', [review(user: null, team: [id: 7]), review(),
    review(user: [login: 'bob'], state: 'APPROVED', submitted_at: '2026-10-20T12:00:00Z')], 1)
  t.route('/teams/7/members', [[login: 'alice'], [login: 'author']], 1)
  t.route('/teams/7/members', [[login: 'bob'], [login: 'carol']], 2)
  assert t.report().messages*.handle == ['alice', 'carol']
}
test('a recent individual request delays an older team request') { t ->
  t.route(repo + '/pulls/1/reviews', [review(user: null, team: [id: 7]),
    review(id: 2, submitted_at: '2026-10-21T12:00:00Z')], 1)
  t.route('/teams/7/members', [[login: 'alice']], 1)
  assert !t.report().messages
}
test('hidden invalid and noreply addresses are unresolved') { t ->
  ['', 'bad', 'alice@noreply.example.test', 'noreply@example.test',
   'alice@no-reply.example.test', 'alice@example.test\nBcc: victim@example.test'].each { email ->
    t.route('/users/alice', [email: email])
    def report = t.report()
    assert !report.messages
    assert report.unresolved == ['alice']
  }
}
test('invalid configuration and schemas fail safely') { t ->
  ['-1', 'NaN', 'Infinity', 'not a number'].each { age -> t.fails { t.report(age: age) } }
  [[message: 'denied'], [null], [[state: 'UNKNOWN']]].each { value ->
    t.route(repo + '/pulls/1/reviews', value, 1)
    t.fails { t.report() }
  }
}
test('insecure or credential bearing base URLs fail') { t ->
  ['http://git.test', 'https://user:secret@git.test', 'https://git.test?secret=x', 'https://git.test/#x'].each { url ->
    t.fails { t.script.collectReminders(url, 'STAR/star-sw', '24', '', now) }
  }
}
test('HTTP errors are sanitized and prevent sending previously prepared messages') { t ->
  t.route('/users/alice', [message: 'test-secret'], 0, [:], 401)
  t.fails { t.script.runReminderJob() }
  assert !t.mails
}
test('dry run runs through the delivery entry point without sending email or using a workspace') { t ->
  t.script.runReminderJob()
  assert !t.mails
  assert t.logs.any { it.startsWith('DRY RUN: Hello @alice,') }
  assert t.logs.any { it.contains('Prepared 1 personalized') }
}
test('normal delivery sends personalized messages using Jenkins mail') { t ->
  t.binding.getVariable('params').DRY_RUN = false
  t.script.runReminderJob()
  assert t.mails.size() == 1
  assert t.mails[0].to == 'alice@example.test'
  assert t.mails[0].mimeType == 'text/plain'
}
test('unresolved addresses mark the job unstable without sending') { t ->
  t.route('/users/alice', [email: ''])
  t.script.runReminderJob()
  assert !t.mails
  assert t.warnings.size() == 1
}
test('reviewer handle selection limits actual email recipients') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob'])], 1)
  t.binding.getVariable('params').REVIEWER_HANDLES = 'alice'
  t.binding.getVariable('params').DRY_RUN = false
  t.script.runReminderJob()
  assert t.mails*.to == ['alice@example.test']
}
test('reviewer handle selection limits dry-run messages and profile lookups') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob'])], 1)
  t.route('/users/bob', [message: 'private profile'], 0, [:], 403)
  t.binding.getVariable('params').REVIEWER_HANDLES = 'alice'
  t.script.runReminderJob()
  assert !t.mails
  assert t.logs.any { it.startsWith('DRY RUN: Hello @alice,') }
  assert !t.logs.any { it.contains('@bob') }
  assert !t.warnings
  assert !t.calls.any { it.url.endsWith('/users/bob') }
}
test('reviewer handles accept commas whitespace optional at signs and mixed case') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob']),
    review(user: [login: 'carol'])], 1)
  def report = t.report(reviewers: ' ALICE, @bob\n alice\tBOB, ')
  assert report.messages*.handle == ['alice', 'bob']
  assert report.messages*.to == ['alice@example.test', 'bob@example.test']
  assert !t.calls.any { it.url.endsWith('/users/carol') }
}
test('blank and missing reviewer lists include all eligible reviewers') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob'])], 1)
  [null, '', ' \n\t '].each { handles ->
    assert t.script.collectReminders(base, 'STAR/star-sw', '24', handles, now).messages*.handle == ['alice', 'bob']
  }
}
test('unknown handles and completed reviewers do not fall back to all recipients') { t ->
  t.route(repo + '/pulls/1/reviews', [review(), review(user: [login: 'bob'], state: 'APPROVED')], 1)
  assert !t.report(reviewers: 'unknown, bob').messages
  assert !t.calls.any { it.url.contains('/users/') }
}
test('reviewer handle selection also limits expanded team members') { t ->
  t.route(repo + '/pulls/1/reviews', [review(user: null, team: [id: 7])], 1)
  t.route('/teams/7/members', [[login: 'alice'], [login: 'bob'], [login: 'carol']], 1)
  assert t.report(reviewers: 'CAROL').messages*.handle == ['carol']
  assert !t.calls.any { it.url.endsWith('/users/alice') || it.url.endsWith('/users/bob') }
}
test('malformed reviewer lists fail before reading Gitea or sending email') { t ->
  [', ,', '@', 'alice@example.test', 'alice/bob', '[alice]', '.', '..'].each { handles ->
    t.fails { t.report(reviewers: handles) }
  }
  assert !t.calls
  assert !t.mails
}
println "${passed} behavioral tests passed."
