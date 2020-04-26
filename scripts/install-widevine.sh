#!/bin/bash
#script to download and extract widevine compements, tested on unbutu 20.04

#Uninstall the files
if [ "$1" == "uninstall" ]; then
    echo "Uninstalling libwidevinecdm.so"
    sudo rm /usr/lib/chromium/libwidevinecdm.so
    exit
fi

#Create temp directory
tmp_dir=$(mktemp -d)
echo $tmp_dir
cd $tmp_dir

#set urls and checksums
url1="https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
file1=$(basename "$url1")
sha256_1=("229b35f0d41bbb6edd98ce4ab8305994a0f5cd1ac4d9817571f07365b2d1ad80")

#Download Files
wget $url1 -P $tmp_dir

#extract the files
ar -vx $tmp_dir/$file1
tar -xvf $tmp_dir/data.tar.xz --strip-components 4 ./opt/google/chrome/WidevineCdm/_platform_specific/linux_x64/libwidevinecdm.so

#install the files
echo "Installing libwidevinecdm.so to /usr/lib/chromium"
sudo mkdir -p /usr/lib/chromium
sudo install -Dm644 $tmp_dir/WidevineCdm/_platform_specific/linux_x64/libwidevinecdm.so -t /usr/lib/chromium
