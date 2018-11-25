#!/usr/bin/env bash

apt install $(grep -vE "^\s*#" scripts/ci/linux/requirements.txt  | tr "\n" " ")
