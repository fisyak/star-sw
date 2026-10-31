"""Offline behavioral tests; no Jenkins, SMTP, or live Gitea access required."""

import contextlib
import copy
from datetime import datetime, timedelta, timezone
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
from urllib.error import HTTPError, URLError
from urllib.parse import parse_qs, urlsplit

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from mgr import reviewer_reminders as reminders


NOW = datetime(2026, 10, 21, 13, tzinfo=timezone.utc)
BASE = "https://git.example.test/gitea"


def pull(number=1, **changes):
    result = {
        "number": number, "state": "open", "merged": False, "draft": False,
        "title": "Fix detector calibration", "user": {"login": "author"},
        "created_at": (NOW - timedelta(days=5)).isoformat(),
        # Gitea can include a completed reviewer in this field.
        "requested_reviewers": [{"login": "bob"}, {"login": "alice"}],
    }
    result.update(changes)
    return result


def review(handle="alice", state="REQUEST_REVIEW", hours=48, **changes):
    result = {
        "id": 1, "state": state, "dismissed": False,
        "user": {"login": handle}, "team": None,
        "submitted_at": (NOW - timedelta(hours=hours)).isoformat(),
    }
    result.update(changes)
    return result


class Response(io.BytesIO):
    def __init__(self, data, headers=None):
        super().__init__(json.dumps(data).encode())
        self.headers = headers or {}


class Transport:
    """Only replace the network transport; exercise real client and selection."""

    def __init__(self):
        self.routes = {}
        self.calls = []

    def page(self, path, data, page=1, headers=None):
        self.routes[(path, page)] = (data, headers)

    def open(self, request, timeout):
        self.calls.append(request)
        parsed = urlsplit(request.full_url)
        page = int(parse_qs(parsed.query).get("page", [0])[0])
        key = (parsed.path[len("/gitea/api/v1"):], page)
        if key not in self.routes and page > 1:
            return Response([])
        if key not in self.routes:
            raise AssertionError("Unexpected API request: {}".format(key))
        data, headers = self.routes[key]
        if isinstance(data, Exception):
            raise data
        return Response(copy.deepcopy(data), headers)


class ReminderTests(unittest.TestCase):
    def setUp(self):
        self.transport = Transport()
        self.client = reminders.GiteaClient(BASE, "test-secret", opener=self.transport)
        self.transport.page("/repos/STAR/star-sw/pulls", [pull()])
        self.transport.page("/repos/STAR/star-sw/pulls/1", pull(), page=0)
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", [review()])
        for handle in ("alice", "bob", "carol"):
            self.transport.page("/users/" + handle,
                                {"login": handle, "email": handle + "@example.test"}, page=0)

    def collect(self, **kwargs):
        return reminders.collect_reminders(self.client, "STAR/star-sw", now=NOW, **kwargs)

    def test_only_pending_requested_reviewer_gets_personalized_digest(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [review(), review("bob", "APPROVED")])
        report = self.collect()
        self.assertEqual([m["handle"] for m in report["messages"]], ["alice"])
        message = report["messages"][0]
        self.assertEqual(message["to"], "alice@example.test")
        self.assertIn(BASE + "/STAR/star-sw/pulls/1", message["body"])
        self.assertIn("@alice", message["body"])
        self.assertNotIn("bob@example.test", message["body"])

    def test_each_reviewer_sees_only_their_assigned_prs(self):
        self.transport.page("/repos/STAR/star-sw/pulls", [pull(), pull(2)])
        self.transport.page("/repos/STAR/star-sw/pulls/2", pull(2), page=0)
        self.transport.page("/repos/STAR/star-sw/pulls/2/reviews", [review("bob")])
        messages = {m["handle"]: m for m in self.collect()["messages"]}
        self.assertEqual(messages["alice"]["pr_numbers"], [1])
        self.assertEqual(messages["bob"]["pr_numbers"], [2])

    def test_multiple_prs_are_grouped_into_one_message_per_reviewer(self):
        self.transport.page("/repos/STAR/star-sw/pulls", [pull(), pull(2)])
        self.transport.page("/repos/STAR/star-sw/pulls/2", pull(2), page=0)
        self.transport.page("/repos/STAR/star-sw/pulls/2/reviews", [review()])
        messages = self.collect()["messages"]
        self.assertEqual(len(messages), 1)
        self.assertEqual(messages[0]["pr_numbers"], [1, 2])

    def test_prs_and_reviews_paginate_even_if_server_clamps_page_size(self):
        self.transport.page("/repos/STAR/star-sw/pulls", [pull(2)], page=2)
        self.transport.page("/repos/STAR/star-sw/pulls/2", pull(2), page=0)
        self.transport.page("/repos/STAR/star-sw/pulls/2/reviews", [review("bob", "APPROVED")])
        self.transport.page("/repos/STAR/star-sw/pulls/2/reviews", [review()], page=2)
        self.assertEqual(self.collect()["messages"][0]["pr_numbers"], [1, 2])

    def test_empty_filtered_page_with_next_link_is_not_end_of_reviews(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", [],
                            headers={"Link": '<https://git.example.test/reviews?page=2>; rel="next"'})
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", [review()], page=2)
        self.assertEqual(len(self.collect()["messages"]), 1)

    def test_completed_dismissed_and_unpublished_reviews_do_not_trigger_mail(self):
        for state, dismissed in [("APPROVED", False), ("REJECTED", False),
                                 ("COMMENT", False), ("PENDING", False),
                                 ("REQUEST_REVIEW", True)]:
            with self.subTest(state=state, dismissed=dismissed):
                self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                                    [review(state=state, dismissed=dismissed)])
                self.assertEqual(self.collect()["messages"], [])

    def test_re_requested_review_after_approval_is_reminded(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [review(state="APPROVED", hours=100, id=2), review(id=3)])
        self.assertEqual(len(self.collect()["messages"]), 1)

    def test_later_completed_review_suppresses_old_request_regardless_of_order(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [review(state="APPROVED", hours=25, id=2), review()])
        self.assertEqual(self.collect()["messages"], [])

    def test_unpublished_review_does_not_hide_outstanding_request(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [review(), review(state="PENDING", hours=1, id=2)])
        self.assertEqual(len(self.collect()["messages"]), 1)

    def test_recent_assignment_or_re_request_waits_for_threshold(self):
        for fields in ({"hours": 1}, {"hours": 48, "updated_at": NOW.isoformat()}):
            with self.subTest(fields=fields):
                self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", [review(**fields)])
                self.assertEqual(self.collect()["messages"], [])

    def test_exact_age_threshold_is_included_and_timezones_are_normalized(self):
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [review(submitted_at="2026-10-20T09:00:00-04:00")])
        self.assertEqual(len(self.collect()["messages"]), 1)

    def test_closed_merged_draft_wip_young_and_unassigned_prs_are_skipped(self):
        for change in ({"state": "closed"}, {"merged": True}, {"draft": True},
                       {"title": "WIP: fix"}, {"title": "[WIP] fix"},
                       {"created_at": NOW.isoformat()}):
            with self.subTest(change=change):
                self.transport.page("/repos/STAR/star-sw/pulls/1", pull(**change), page=0)
                self.assertEqual(self.collect()["messages"], [])
        self.transport.page("/repos/STAR/star-sw/pulls/1", pull(), page=0)
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", [])
        self.assertEqual(self.collect()["messages"], [])

    def test_team_requests_expand_paginated_members_and_exclude_author_and_reviewed(self):
        team = review(user=None, team={"id": 7, "name": "detector"})
        self.transport.page("/repos/STAR/star-sw/pulls/1/reviews",
                            [team, review(), review("bob", "APPROVED", hours=25)])
        self.transport.page("/teams/7/members", [{"login": "alice"}, {"login": "author"}])
        self.transport.page("/teams/7/members", [{"login": "bob"}, {"login": "carol"}], page=2)
        self.assertEqual([m["handle"] for m in self.collect()["messages"]], ["alice", "carol"])

    def test_hidden_or_invalid_email_is_reported_without_guessing(self):
        for email in ("", "alice@noreply.example.test", "alice@no-reply.example.test",
                      "alice@example.test\nBcc: victim@example.test", "bad"):
            with self.subTest(email=email):
                self.transport.page("/users/alice", {"login": "alice", "email": email}, page=0)
                report = self.collect()
                self.assertEqual(report["messages"], [])
                self.assertEqual(report["unresolved"], ["alice"])

    def test_explicit_email_override_is_case_insensitive(self):
        self.transport.page("/users/alice", {"email": ""}, page=0)
        message = self.collect(email_overrides={"ALICE": "real@example.test"})["messages"][0]
        self.assertEqual(message["to"], "real@example.test")

    def test_gitea_token_is_only_in_header_and_errors_do_not_echo_server_body(self):
        self.collect()
        self.assertTrue(all(r.get_method() == "GET" for r in self.transport.calls))
        self.assertTrue(all(r.get_header("Authorization") == "token test-secret"
                            for r in self.transport.calls))
        self.assertTrue(all("test-secret" not in r.full_url for r in self.transport.calls))
        self.transport.page("/repos/STAR/star-sw/pulls", HTTPError(
            "secret-url", 401, "test-secret", {}, io.BytesIO(b"test-secret")))
        with self.assertRaises(reminders.ReminderError) as caught:
            self.collect()
        self.assertIn("401", str(caught.exception))
        self.assertNotIn("test-secret", str(caught.exception))

    def test_api_failure_or_unexpected_schema_prevents_report(self):
        for data in ({"message": "Access denied"}, [None], URLError("unavailable")):
            with self.subTest(data=data):
                self.transport.page("/repos/STAR/star-sw/pulls/1/reviews", data)
                with self.assertRaises(reminders.ReminderError):
                    self.collect()

    def test_no_open_prs_produces_no_messages_or_profile_requests(self):
        self.transport.page("/repos/STAR/star-sw/pulls", [])
        self.assertEqual(self.collect()["messages"], [])
        self.assertFalse(any("/users/" in r.full_url for r in self.transport.calls))

    def test_cli_writes_mail_files_and_never_sends_email(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(reminders, "GiteaClient", return_value=self.client), \
                    patch.dict("os.environ", {"GITEA_TOKEN": "test-secret"}), \
                    contextlib.redirect_stdout(io.StringIO()):
                status = reminders.main(["--base-url", BASE, "--repository", "STAR/star-sw",
                                         "--min-age-hours", "0", "--output-dir", directory])
            self.assertEqual(status, 0)
            output = Path(directory)
            self.assertEqual((output / "count.txt").read_text().strip(), "1")
            self.assertEqual((output / "message-0.to").read_text().strip(), "alice@example.test")
            self.assertIn("/pulls/1", (output / "message-0.txt").read_text())

    def test_insecure_or_credential_bearing_base_urls_are_rejected(self):
        for url in ("http://git.example.test", "https://user:secret@git.example.test",
                    "https://git.example.test?token=secret", "https://git.example.test/#frag"):
            with self.subTest(url=url), self.assertRaises(reminders.ReminderError):
                reminders.GiteaClient(url, "secret")

    def test_invalid_age_is_rejected(self):
        for value in (-1, float("nan"), float("inf")):
            with self.subTest(value=value), self.assertRaises(reminders.ReminderError):
                self.collect(min_age_hours=value)


if __name__ == "__main__":
    unittest.main()
