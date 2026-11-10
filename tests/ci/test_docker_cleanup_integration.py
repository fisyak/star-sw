"""Opt-in real Docker lifecycle test; creates and removes only its own fixtures.

Run with STAR_DOCKER_INTEGRATION=1 python3 -m unittest discover -s tests/ci
An existing image may be selected with STAR_DOCKER_TEST_IMAGE.
"""
import os
from pathlib import Path
import re
import subprocess
import unittest
import uuid


@unittest.skipUnless(os.environ.get('STAR_DOCKER_INTEGRATION') == '1',
                     'set STAR_DOCKER_INTEGRATION=1 to use real Docker')
class DockerCleanupIntegrationTests(unittest.TestCase):
    def test_interrupted_build_cleanup_preserves_other_build(self):
        source = (Path(__file__).resolve().parents[2] / 'Jenkinsfile').read_text()
        script = re.search(r"def cleanupContainers\(\) \{.*?bash '''(.*?)'''",
                           source, re.S)[1]
        image = os.environ.get('STAR_DOCKER_TEST_IMAGE', 'alpine:3.16.3')
        build = 'star-cleanup-test-' + uuid.uuid4().hex
        names, volumes = [], []

        def docker(*args, check=True):
            return subprocess.run(['docker', *args], check=check,
                                  capture_output=True, text=True)

        def create(suffix, label, *args):
            name = build + '-' + suffix
            names.append(name)
            docker('create', '--name', name, '--label',
                   'org.star.bnl.ci-build=' + label, *args)
            return name

        try:
            # Data owner is deliberately created before its consumers, as in CI.
            owner = create('data', build, '--volume', '/star', image,
                           'sh', '-c', 'echo fixture > /star/fixture')
            docker('start', '-a', owner)
            volume = docker('inspect', '--format',
                            '{{range .Mounts}}{{.Name}}{{end}}', owner).stdout.strip()
            volumes.append(volume)
            failed = create('failed', build, '--volumes-from', owner,
                            image, 'sh', '-c', 'exit 1')
            docker('start', '-a', failed, check=False)
            self.assertEqual(docker('inspect', '--format', '{{.State.ExitCode}}',
                                    failed).stdout.strip(), '1')
            running = create('running', build, '--volumes-from', owner,
                             image, 'sleep', '300')
            docker('start', running)
            other = create('other-build', build + '-other', '--volume', '/star',
                           image, 'sleep', '300')
            docker('start', other)
            other_volume = docker('inspect', '--format',
                                  '{{range .Mounts}}{{.Name}}{{end}}', other).stdout.strip()
            volumes.append(other_volume)
            environment = dict(os.environ, CI_BUILD_ID=build)
            for _ in range(2):  # Cleanup must also tolerate being repeated.
                subprocess.run(['bash', '-euo', 'pipefail', '-c', script],
                               env=environment, check=True, capture_output=True)
            for name in (owner, failed, running):
                self.assertNotEqual(docker('inspect', name, check=False).returncode, 0)
            self.assertNotEqual(docker('volume', 'inspect', volume,
                                       check=False).returncode, 0)
            self.assertEqual(docker('inspect', '--format', '{{.State.Running}}',
                                    other).stdout.strip(), 'true')
            docker('volume', 'inspect', other_volume)
        finally:
            for name in reversed(names):
                docker('rm', '-fv', name, check=False)
            for volume in volumes:
                docker('volume', 'rm', volume, check=False)


if __name__ == '__main__':
    unittest.main()
