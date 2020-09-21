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

#Download Files
wget $url1 -P $tmp_dir

#extract the files
ar -vx $tmp_dir/$file1
tar -xvf $tmp_dir/data.tar.xz --strip-components 4 ./opt/google/chrome/WidevineCdm/_platform_specific/linux_x64/libwidevinecdm.so

#install the files
echo "Installing libwidevinecdm.so to /usr/lib/chromium"
sudo mkdir -p /usr/lib/chromium
sudo install -Dm644 $tmp_dir/WidevineCdm/_platform_specific/linux_x64/libwidevinecdm.so -t /usr/lib/chromium

if [ -d "/var/lib/flatpak/app/com.gitlab.ColinDuquesnoy.MellowPlayer/current/active/files/bin" ]; then
  echo "Installing libwidevinecdm.so for use in flatpak"
  sudo cp /usr/lib/chromium/libwidevinecdm.so /var/lib/flatpak/app/com.gitlab.ColinDuquesnoy.MellowPlayer/current/active/files/bin
fi