#!/usr/bin/env bash

sudo apt install $(grep -vE "^\s*#" scripts/ci/linux/requirements.txt  | tr "\n" " ")