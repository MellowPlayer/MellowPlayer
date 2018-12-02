"""
Utility script to easily change the MellowPlayer version in CMakeLists.txt, appveyor.yml, sphinx doc,...

Usage:

python scripts/set_version.py 3.4.90
"""
import re

import sys

new_version = sys.argv[1]
version_major, version_minor, version_patch = new_version.split(".")


def update_conf_py_version():
    file_name = 'docs/conf.py'
    with open(file_name, 'r') as f:
        content = f.read()
    content = re.sub("version = .*", "version = '%s.%s'" % (version_major, version_minor), content)
    content = re.sub("release = .*", "release = '%s'" % new_version, content)

    with open(file_name, 'w') as f:
        f.write(content)


def update_cmake():
    file_name = 'CMakeLists.txt'
    with open(file_name, 'r') as f:
        content = f.read()
    content = re.sub("set\(VERSION_MAJOR .*\)", "set(VERSION_MAJOR %s)" % version_major, content)
    content = re.sub("set\(VERSION_MINOR .*\)", "set(VERSION_MINOR %s)" % version_minor, content)
    content = re.sub("set\(VERSION_PATCH .*\)", "set(VERSION_PATCH %s)" % version_patch, content)

    with open(file_name, 'w') as f:
        f.write(content)


def update_appveyor():
    file_name = '.appveyor.yml'
    with open(file_name, 'r') as f:
        content = f.read()
    content = re.sub('version: .*', "version: %s.{build}" % new_version, content)
    with open(file_name, 'w') as f:
        f.write(content)


def update_gitlab():
    file_name = '.gitlab-ci.yml'
    with open(file_name, 'r') as f:
        content = f.read()
    content = re.sub("FULL_VERSION: .*", "FULL_VERSION: '%s.${CI_PIPELINE_IID}'" % new_version, content)
    with open(file_name, 'w') as f:
        f.write(content)


update_conf_py_version()
update_cmake()
update_appveyor()
update_gitlab()
