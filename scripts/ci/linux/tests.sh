#!/usr/bin/env bash

set -e

cd build

ctest --output-on-failure
