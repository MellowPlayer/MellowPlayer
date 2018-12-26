import datetime
import os
import sys

import gitlab

excluded_labels = ['duplicate', 'question', 'invalid', 'wontfix', 'rejected', 'technical task', 'news', "annoucement", 'not our bug', 'discussion', 'website', 'support']


def find_milestone_id(project):
    global milestone_id
    milestone_id = None
    for milestone in project.milestones.list():
        if milestone.title == milestone_title:
            milestone_id = milestone.id
            break

    if milestone_id is None:
        print("failed to find requested milestone")
        sys.exit(1)

    return milestone_id


def find_milestone_issues(project):
    issues = []
    for issue in project.issues.list(all=True):
        if issue.milestone is not None and issue.milestone["id"] == milestone_id and issue.state == "closed" and not is_excluded(issue):
            issues.append(issue)
    return issues


def is_excluded(issue):
    for label in issue.labels:
        if label in excluded_labels:
            return True
    return False


def find_milestone_merge_requests(project):
    global merge_requests
    merge_requests = []
    for mr in project.mergerequests.list(all=True):
        if mr.milestone is not None and mr.milestone["id"] == milestone_id:
            merge_requests.append(mr)
    return merge_requests


def title(milestone_title):
    now = datetime.datetime.now()
    return f"## [{milestone_title}](https://gitlab.com/ColinDuquesnoy/MellowPlayer/tree/{milestone_title}) ({now.year}-{now.month}-{now.day})"


def full_changelog(previous_milestone, new_milestone):
    return f"[Full Changelog](https://gitlab.com/ColinDuquesnoy/MellowPlayer/compare/{previous_milestone}...{new_milestone})"


def is_feature(issue):
    for label in issue.labels:
        if "feature" in label:
            return True
    return False


def is_bug(issue):
    for label in issue.labels:
        if "bug" in label or "broken" in label:
            return True
    return False


def implemented_features(issues):
    formatted_issues = [
        ""
        "**Implemented enhancements:**",
        ""
    ]
    for issue in issues:
        if is_feature(issue):
            formatted_issues.append(format_issue(issue))
    formatted_issues.append("")
    return formatted_issues


def fixed_bugs(issues):
    formatted_issues = [
        ""
        "**Fixed bugs:**",
        ""
    ]
    for issue in issues:
        if is_bug(issue):
            formatted_issues.append(format_issue(issue))
    formatted_issues.append("")
    return formatted_issues


def closed_issues(issues):
    formatted_issues = [
        "",
        "**Closed issues:**",
        ""
    ]
    for issue in issues:
        if not is_bug(issue) and not is_feature(issue):
            formatted_issues.append(format_issue(issue))
    formatted_issues.append("")
    return formatted_issues


def merged_merge_requests(merge_requests):
    formatted_issues = [
        "",
        "**Merged merge requests:**",
        ""
    ]
    for mr in merge_requests:
        formatted_issues.append(format_merge_request(mr))
    formatted_issues.append("")
    return formatted_issues


def format_issue(issue):
    return f"- {issue.title} [\\#{issue.iid}](https://gitlab.com/ColinDuquesnoy/MellowPlayer/issues/{issue.iid})"


def format_merge_request(mr):
    formatted = f"- {mr.title} [\\#{mr.iid}](https://gitlab.com/ColinDuquesnoy/MellowPlayer/merge_requests/{mr.iid})"
    author = mr.author['username']
    if author != "ColinDuquesnoy":
        formatted += f" ([{author}](https://gitlab.com/{author}))"
    return formatted


def write_changelog(content):
    with open('CHANGELOG.md', 'r') as f:
        initial_content = f.read()
    initial_content = '\n'.join(initial_content.splitlines()[1:])

    with open('CHANGELOG.md', 'w') as f:
        f.write("# Change log\n\n" + content + initial_content)


previous_milestone_title = sys.argv[1]
milestone_title = sys.argv[2]
gl = gitlab.Gitlab("https://gitlab.com", private_token=os.getenv("GITLAB_TOKEN"))
project = gl.projects.get("9602590")
milestone_id = find_milestone_id(project)
issues = find_milestone_issues(project)
merge_requests = find_milestone_merge_requests(project)

content = [
    title(milestone_title),
    full_changelog(previous_milestone_title, milestone_title),
    ""
]

content += implemented_features(issues)
content += fixed_bugs(issues)
content += closed_issues(issues)
content += merged_merge_requests(merge_requests)
write_changelog('\n'.join(content))
