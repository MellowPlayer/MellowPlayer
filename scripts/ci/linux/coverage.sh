#!/usr/bin/env bash
set -e

cd build

ctest
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '*/_deps/*' '*tests/*' '*.local/*' '*QQmlObjectListModel*' '*Qt5*/*' '*I*.hpp' '*Qt/5.*' '*3rdparty/*' '*qrc_*' '*moc_*' '/usr/*' '/opt/*' --output-file coverage.info.cleaned
lcov --list coverage.info.cleaned