#!/usr/bin/env bash

set -e

mkdir -p appdir
mkdir -p build && cd build

cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DSTATIC_LIBSTDCPP=TRUE -DUSE_LD_GOLD=FALSE ..
make -j$(nproc)
make DESTDIR=../appdir install
