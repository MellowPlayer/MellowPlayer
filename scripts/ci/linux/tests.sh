#!/usr/bin/env bash

set -e

cd build

xvfb-run ctest --verbose
