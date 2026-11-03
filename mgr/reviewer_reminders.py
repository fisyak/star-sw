#!/usr/bin/env python3
"""Prepare personalized Gitea review reminders; Jenkins handles mail delivery.

Requires Python 3.8+ and only the standard library. Gitea access is read-only.
The token is read from GITEA_TOKEN; optional address overrides are a JSON object
in REVIEWER_EMAIL_OVERRIDES. No email is sent by this program.
"""

import argparse
from datetime import datetime, timedelta, timezone
from email.utils import parseaddr
import json
import math
import os
from pathlib import Path
import re
import sys
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode, urlsplit
from urllib.request import HTTPRedirectHandler, Request, build_opener


class ReminderError(Exception):
    """A configuration, API, or report-generation error safe to show in logs."""


class NoRedirect(HTTPRedirectHandler):
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        # Never forward the API token to a redirect target (including sign-in).
        return None


class GiteaClient:
    def __init__(self, base_url, token, opener=None):
        parsed = urlsplit(base_url)
        if (parsed.scheme != "https" or not parsed.hostname or parsed.username
                or parsed.password or parsed.query or parsed.fragment):
            raise ReminderError("Use an HTTPS Gitea base URL without credentials, query, or fragment.")
        if not token or any(c.isspace() for c in token):
            raise ReminderError("GITEA_TOKEN must contain an API token.")
        self.base_url = base_url.rstrip("/")
        self.opener = opener or build_opener(NoRedirect())
        self.token = token

    def request(self, path, params=None):
        url = self.base_url + "/api/v1" + path
        if params:
            url += "?" + urlencode(params)
        request = Request(url, headers={"Authorization": "token " + self.token,
                                        "Accept": "application/json"})
        try:
            with self.opener.open(request, timeout=30) as response:
                return json.load(response), response.headers
        except HTTPError as error:
            raise ReminderError("Gitea GET {} failed: HTTP {}.".format(path, error.code)) from None
        except (URLError, OSError, ValueError):
            # Do not echo server bodies, URLs containing credentials, or tokens.
            raise ReminderError("Gitea GET {} failed: network error or invalid JSON.".format(path)) from None

    def get(self, path):
        data, _ = self.request(path)
        if not isinstance(data, dict):
            raise ReminderError("Gitea GET {} did not return an object.".format(path))
        return data

    def pages(self, path, params=None):
        page = 1
        seen = set()
        while True:
            query = dict(params or {}, page=page, limit=50)
            data, headers = self.request(path, query)
            if not isinstance(data, list) or any(not isinstance(item, dict) for item in data):
                raise ReminderError("Gitea GET {} did not return a list of objects.".format(path))
            # Gitea may clamp the requested page size; a short page is not EOF.
            # Review pages can also be empty after unpublished reviews are hidden.
            next_page = re.search(r'rel=["\']?next\b', headers.get("Link", ""))
            if not data and not next_page:
                return
            if data:
                fingerprint = json.dumps(data, sort_keys=True)
                if fingerprint in seen:
                    raise ReminderError("Gitea pagination repeated a page for {}.".format(path))
                seen.add(fingerprint)
                yield from data
            page += 1


def timestamp(value):
    parsed = datetime.fromisoformat(value.replace("Z", "+00:00"))
    if parsed.tzinfo is None:
        raise ReminderError("Gitea returned a timestamp without a timezone.")
    return parsed.astimezone(timezone.utc)


def handle_of(user):
    handle = user["login"]
    if (not isinstance(handle, str) or not handle or handle in (".", "..")
            or any(c.isspace() or c in "/\\" for c in handle)):
        raise ReminderError("Gitea returned an invalid reviewer handle.")
    return handle


def latest_reviews(reviews, created):
    """Keep the latest published, non-dismissed review for each user/team.

    requested_reviewers includes completed reviewers on some Gitea versions.
    REQUEST_REVIEW is the actual outstanding request; PENDING is an unpublished
    draft review and must not replace a still-outstanding request.
    """
    latest = {}
    for review in reviews:
        state = review["state"]
        if state == "PENDING" or review.get("dismissed"):
            continue
        if state not in ("REQUEST_REVIEW", "APPROVED", "REJECTED", "COMMENT"):
            raise ReminderError("Gitea returned an unsupported review state.")
        team = review.get("team")
        if team:
            team_id = int(team["id"])
            if team_id <= 0:
                raise ReminderError("Gitea returned an invalid team ID.")
            key = ("team", team_id)
        else:
            key = ("user", handle_of(review["user"]).casefold())
        updated = review.get("updated_at") or review.get("submitted_at")
        when = timestamp(updated) if updated else created
        order = (when, int(review["id"]))
        if key not in latest or order > latest[key][0]:
            latest[key] = (order, review)
    return latest


def deliverable_email(value):
    if not isinstance(value, str) or any(c.isspace() for c in value):
        return False
    _, address = parseaddr(value)
    if address != value or address.count("@") != 1:
        return False
    local, domain = address.lower().split("@")
    return bool(local and "." in domain and not domain.startswith(("noreply.", "no-reply."))
                and local not in ("noreply", "no-reply"))


def collect_reminders(client, repository, min_age_hours=24, now=None, email_overrides=None):
    if not math.isfinite(min_age_hours) or min_age_hours < 0:
        raise ReminderError("Minimum age must be a finite, non-negative number of hours.")
    parts = repository.split("/")
    if len(parts) != 2 or any(not p or p in (".", "..") for p in parts):
        raise ReminderError("Repository must have the form owner/name.")
    repo_path = "/repos/" + "/".join(quote(p, safe="") for p in parts)
    now = now or datetime.now(timezone.utc)
    cutoff = now - timedelta(hours=min_age_hours)
    overrides = {k.casefold(): v for k, v in (email_overrides or {}).items()}
    grouped = {}
    teams = {}
    seen_prs = set()
    try:
        for summary in client.pages(repo_path + "/pulls", {"state": "open"}):
            number = int(summary["number"])
            if number <= 0:
                raise ReminderError("Gitea returned an invalid PR number.")
            if number in seen_prs:
                continue
            seen_prs.add(number)
            # Re-fetch current details: a PR can close or become a draft during pagination.
            pr = client.get(repo_path + "/pulls/" + str(number))
            title = pr["title"]
            created = timestamp(pr["created_at"])
            if (pr["state"] != "open" or pr.get("merged") or pr.get("draft")
                    or re.match(r"\s*(?:\[wip\]|wip:|draft:)", title, re.IGNORECASE)
                    or created > cutoff):
                continue
            author = handle_of(pr["user"]).casefold()
            reviews = latest_reviews(client.pages(repo_path + "/pulls/{}/reviews".format(number)), created)
            candidates = {}
            for key, (order, review) in reviews.items():
                if review["state"] != "REQUEST_REVIEW" or max(created, order[0]) > cutoff:
                    continue
                if key[0] == "team":
                    if key[1] not in teams:
                        teams[key[1]] = list(client.pages("/teams/{}/members".format(key[1])))
                    members = teams[key[1]]
                else:
                    members = [review["user"]]
                for member in members:
                    handle = handle_of(member)
                    canonical = handle.casefold()
                    # A member who already responded to a team request is done.
                    individual = reviews.get(("user", canonical))
                    if key[0] == "team" and individual:
                        if individual[1]["state"] != "REQUEST_REVIEW" and individual[0][0] >= order[0]:
                            continue
                        if individual[1]["state"] == "REQUEST_REVIEW" and individual[0][0] > cutoff:
                            continue
                    if canonical != author:
                        candidates[canonical] = handle
            for canonical, handle in candidates.items():
                entry = grouped.setdefault(canonical, {"handle": handle, "prs": []})
                entry["prs"].append({"number": number, "title": " ".join(title.split()),
                                     "author": handle_of(pr["user"]),
                                     "created": created})
        messages, unresolved = [], []
        for canonical, entry in sorted(grouped.items()):
            handle = entry["handle"]
            if canonical in overrides:
                email = overrides[canonical]
            else:
                email = client.get("/users/" + quote(handle, safe="")).get("email", "")
            if not deliverable_email(email):
                unresolved.append(handle)
                continue
            prs = sorted(entry["prs"], key=lambda pr: pr["number"])
            lines = ["Hello @{},".format(handle), "",
                     "Please review these pull requests in {}:".format(repository), ""]
            for pr in prs:
                lines.extend(["#{}: {}".format(pr["number"], pr["title"]),
                              "Author: @{}; PR age: {:.1f} days".format(
                                  pr["author"], (now - pr["created"]).total_seconds() / 86400),
                              "{}/{}/pulls/{}".format(client.base_url, repository, pr["number"]), ""])
            lines.extend(["These review requests have been pending for at least {:g} hours.".format(min_age_hours),
                          "This weekday reminder stops when you submit your review, the request is removed,",
                          "or the PR is closed or marked as a draft.", ""])
            messages.append({"handle": handle, "to": email,
                             "subject": "[{}] {} pull request(s) awaiting your review".format(repository, len(prs)),
                             "body": "\n".join(lines), "pr_numbers": [pr["number"] for pr in prs]})
        return {"messages": messages, "unresolved": unresolved}
    except (KeyError, TypeError, ValueError, OverflowError):
        raise ReminderError("Gitea returned malformed PR, review, team, or user data.") from None


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base-url", default="https://git.racf.bnl.gov/gitea")
    parser.add_argument("--repository", default="STAR/star-sw")
    parser.add_argument("--min-age-hours", type=float, default=24)
    parser.add_argument("--output-dir", type=Path, default=Path("reviewer-reminders"))
    args = parser.parse_args(argv)
    try:
        overrides = json.loads(os.environ.get("REVIEWER_EMAIL_OVERRIDES", "{}"))
        if not isinstance(overrides, dict) or any(not isinstance(k, str) for k in overrides):
            raise ReminderError("REVIEWER_EMAIL_OVERRIDES must be a JSON object mapping handles to addresses.")
        client = GiteaClient(args.base_url, os.environ.get("GITEA_TOKEN", ""))
        report = collect_reminders(client, args.repository, args.min_age_hours, email_overrides=overrides)
        args.output_dir.mkdir(parents=True, exist_ok=True)
        for index, message in enumerate(report["messages"]):
            for suffix, field in (("to", "to"), ("subject", "subject"), ("txt", "body")):
                path = args.output_dir / "message-{}.{}".format(index, suffix)
                path.write_text(message[field], encoding="utf-8")
                path.chmod(0o600)
            print("Prepared reminder for @{}: PRs {}".format(message["handle"], message["pr_numbers"]))
        (args.output_dir / "unresolved.txt").write_text("\n".join(report["unresolved"]), encoding="utf-8")
        # Publish the count last, after every API lookup and message write succeeded.
        (args.output_dir / "count.txt").write_text(str(len(report["messages"])) + "\n", encoding="utf-8")
        if report["unresolved"]:
            print("No deliverable Gitea email for: {}. Set REVIEWER_EMAIL_OVERRIDES for these handles.".format(
                ", ".join(report["unresolved"])), file=sys.stderr)
        print("Prepared {} reminder(s); {} unresolved reviewer(s).".format(
            len(report["messages"]), len(report["unresolved"])))
        return 0
    except (ReminderError, OSError, ValueError) as error:
        # Invalid override JSON can contain addresses or other pasted secrets.
        message = str(error) if isinstance(error, ReminderError) else "Invalid configuration or report output failure."
        print("error: " + message, file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
