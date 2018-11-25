#!/usr/bin/env bash

set -e

mkdir -p build && cd build
cmake -DBUILD_TESTS=ON ..
cmake --build . --config Release -- -j $(grep -c ^processor /proc/cpuinfo)
