#!/usr/bin/env bash
set -e
build_type="Release"
build_dir="cmake-build-release"

export QT_PLUGIN_PATH=$PWD/qt/plugins

if [ "$1" == "--debug" ]; then
    build_type="Debug";
    build_dir="cmake-build-debug";
fi

cd $build_dir
ctest -V

if [ "$2" == "--coverage" ]; then
    make coverage;
fi
