#!/usr/bin/env bash

apt update
apt install $(grep -vE "^\s*#" scripts/ci/linux/requirements.txt  | tr "\n" " ")
