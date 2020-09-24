#!/usr/bin/env bash
set -e

mkdir -p build && cd build
cmake -G Ninja -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DENABLE_LCOV_REPORT=ON -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
