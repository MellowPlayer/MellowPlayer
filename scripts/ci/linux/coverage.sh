#!/usr/bin/env bash

set -e

mkdir -p build && cd build
cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DENABLE_LCOV_REPORT=ON -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config DEBUG -- -j $(grep -c ^processor /proc/cpuinfo)
xvfb-run cmake --build . --config DEBUG --target coverage
