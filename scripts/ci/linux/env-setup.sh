#!/usr/bin/env bash

set -e

apt update
apt install $(grep -vE "^\s*#" scripts/ci/linux/requirements.txt  | tr "\n" " ") -y
