#!/usr/bin/env bash

set -e

mkdir -p build && cd build

cmake -G Ninja -DENABLE_QML_LINT=ON ..
cmake --build --target qmllint -- -k 0
