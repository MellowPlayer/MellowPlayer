#!/usr/bin/env bash

set -e

mkdir -p build && cd build

cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..
cmake --build .