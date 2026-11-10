"""Exercise the pipeline's cleanup shell without touching the Docker daemon."""
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


class DockerCleanupTests(unittest.TestCase):
    def run_cleanup(self, docker_script):
        source = (ROOT / 'Jenkinsfile').read_text()
        match = re.search(
            r"def cleanupContainers\(\) \{.*?bash '''(.*?)'''", source, re.S
        )
        self.assertIsNotNone(match, 'pipeline needs final container cleanup')
        with tempfile.TemporaryDirectory() as directory:
            docker = Path(directory) / 'docker'
            docker.write_text('#!/bin/bash\nset -eu\n' + docker_script)
            docker.chmod(0o755)
            removal = Path(directory) / 'removed'
            environment = dict(
                os.environ,
                PATH=directory + ':' + os.environ['PATH'],
                CI_BUILD_ID='build-17',
                REMOVAL=str(removal),
            )
            result = subprocess.run(
                ['bash', '-euo', 'pipefail', '-c', match[1]],
                env=environment, capture_output=True, text=True,
            )
            return result, removal.read_text().strip() if removal.exists() else None

    def test_removes_only_current_build_containers_with_volumes(self):
        result, removed = self.run_cleanup('''
if [[ "$1" == ps ]]; then
    [[ "$*" == "ps -aq --filter label=org.star.bnl.ci-build=build-17" ]] || exit 2
    printf '%s\\n' current-container another-current-container
elif [[ "$1" == rm ]]; then
    [[ "$*" == "rm -fv current-container another-current-container" ]] || exit 3
    echo removed-with-volumes > "$REMOVAL"
else
    exit 4
fi
''')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(removed, 'removed-with-volumes')

    def test_empty_build_does_not_remove_anything(self):
        result, removed = self.run_cleanup('[[ "$1" == ps ]] || exit 9\n')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIsNone(removed)

    def test_failed_listing_is_reported_without_attempting_removal(self):
        result, removed = self.run_cleanup('''
if [[ "$1" == ps ]]; then exit 7; fi
echo unsafe-removal > "$REMOVAL"
''')
        self.assertEqual(result.returncode, 7)
        self.assertIsNone(removed)


if __name__ == '__main__':
    unittest.main()
