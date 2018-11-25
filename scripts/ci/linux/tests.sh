#!/usr/bin/env bash

cd build

xvfb-run ctest --output-on-failure
