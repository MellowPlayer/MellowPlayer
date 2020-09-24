#!/usr/bin/env bash

set -e

cd build

catchsegv ctest --verbose
