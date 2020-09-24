#!/usr/bin/env bash
set -e

cd build

catchsegv ctest --output-on-failure
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '*tests/*' '*.local/*' '*QQmlObjectListModel*' '*Qt5*/*' '*I*.hpp' '*Qt/5.*' '*3rdparty/*' '*qrc_*' '*moc_*' '/usr/*' '/opt/*' --output-file coverage.info.cleaned
lcov --list coverage.info.cleaned