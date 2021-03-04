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
libwidevinecdm_path="$tmp_dir/WidevineCdm/_platform_specific/linux_x64/libwidevinecdm.so"

flatpak_installation=$(flatpak list | grep MellowPlayer)

if [ -z "$flatpak_installation" ]; then
  # Install the files
  echo "Installing libwidevinecdm.so to /usr/lib/chromium"
  sudo mkdir -p /usr/lib/chromium
  sudo install -Dm644 "$libwidevinecdm_path" -t /usr/lib/chromium
else
  echo "Installing libwidevinecdm.so for use in flatpak installation"

  # Prepare for use in flatpak: copy to app plugins dir
  mkdir -p ~/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi
  cp "$libwidevinecdm_path" ~/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi/

  # Override widevine-path
  flatpak_env_override="--widevine-path=$HOME/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi/libwidevinecdm.so --no-sandbox"

  flatpak override --user --env=QTWEBENGINE_CHROMIUM_FLAGS="$flatpak_env_override" com.gitlab.ColinDuquesnoy.MellowPlayer
fi

