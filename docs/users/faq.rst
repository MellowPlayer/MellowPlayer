FAQ & Known issues
==================

Playback does not start on some services such as Soundcloud or Mixcloud... What can I do?
-----------------------------------------------------------------------------------------

Services that don't use flash often requires proprietary audio codecs to be installed on your system. Those codecs are not included in our official releases (AppImage and Windows Installer).

To solve the problem, you need to build MellowPlayer and Qt from sources and make sure you enable propertietary codecs support, see https://doc.qt.io/qt-5.11/qtwebengine-features.html#audio-and-video-codecs

If you're using GNU/Linux, check if a native package of MellowPlayer is available for your distribution and use it instead of AppImage. Native packages usually use system ffmpeg and it should be enought to install extra ffmpeg plugins for the missing proprietary codecs.


.. note:: MP3 is still considered as a proprietary/patented codec prior to Qt 5.11.

.. note:: Services that require proprietary codecs are included in our official releases but won't appear in the application.


The application crashes at startup on GNU/Linux with open source NVIDIA drivers. What can I do?
-----------------------------------------------------------------------------------------------

Qt/QML applications don't work well with the open source NVIDIA drivers (nouveau). It is recommended to **use the proprietary NVIDIA drivers**.

The application crashes at startup on GNU/Linux with proprietary NVIDIA drivers. What can I do?
-----------------------------------------------------------------------------------------------

Make sure you rebooted after your last NVIDIA driver update and make sure to run ``sudo nvidia-xconfig`` before reporting the issue.


There is no music playback on Spotify. What can I do?
-----------------------------------------------------

Make sure you have installed both the proprietary audio codecs (ffmpeg with extra codecs) and the widevine DRM plugin. The DRM plugin can be extracted from chromium binary archive:

.. code-block:: bash

    wget https://archive.archlinux.org/packages/c/chromium/chromium-61.0.3163.100-1-x86_64.pkg.tar.xz
    wget https://dl.google.com/widevine-cdm/1.4.8.1008-linux-x64.zip
    tar -xvf chromium-61.0.3163.100-1-x86_64.pkg.tar.xz
    unzip 1.4.8.1008-linux-x64.zip

    sudo mkdir /usr/lib/chromium
    sudo cp libwidevinecdm.so /usr/lib/chromium
    sudo cp ./usr/lib/chromium/libwidevinecdmadapter.so /usr/lib/chromium
    sudo chmod 644 /usr/lib/chromium/libwidevinecdm.so
    sudo chmod 644 /usr/lib/chromium/libwidevinecdmadapter.so
