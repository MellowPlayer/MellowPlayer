#!/usr/bin/env bash

set -e

DOWNLOAD_URL=$1;
INSTALLATION_DIRECTORY=$2;
ARCHIVE_PATH="/tmp/mellowplayer-connect.tar.gz"

echo "Downloading MellowPlayer.Connect from $DOWNLOAD_URL";
echo "Installation directory: $INSTALLATION_DIRECTORY";

rm -rf $ARCHIVE_PATH


if [ -x "$(command -v wget)" ]; then
    echo "using wget"
    wget -q -O $ARCHIVE_PATH $DOWNLOAD_URL
else
    if [ -x "$(command -v curl)" ]; then
        echo "using curl";
        curl -L $DOWNLOAD_URL -o $ARCHIVE_PATH --fail --silent --show-error
    else
        echo "Could not find curl or wget. Please install one of them and try again..." >&2;
        exit -1
    fi
fi

if test -f "$ARCHIVE_PATH"; then
    echo "$ARCHIVE_PATH exist"
    mkdir -p $INSTALLATION_DIRECTORY
    if [ -x "$(command -v tar)" ]; then
        echo "tar command found";
        tar -zxf $ARCHIVE_PATH --directory $INSTALLATION_DIRECTORY
    else
        echo "Could not find tar. Please install it and try again..." >&2;
        exit -1
    fi
else
    echo "Failed to download linux-x64 archive"
    exit -1
fi