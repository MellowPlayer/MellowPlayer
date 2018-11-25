#!/usr/bin/env bash

mkdir -p build && cd build
cmake -DBUILD_TESTS=ON ..
cmake --build . --config Release -- -j $(grep -c ^processor /proc/cpuinfo)
