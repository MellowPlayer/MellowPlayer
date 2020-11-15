FAQ & Known issues
==================

Playback does not start on some services such as Soundcloud or Mixcloud... What can I do?
-----------------------------------------------------------------------------------------

Services that don't use flash often requires proprietary audio codecs to be installed on your system. Those codecs are not included in our official releases on Windows.

To solve the problem, you need to build MellowPlayer and Qt from sources and make sure you enable propertietary codecs support, see https://doc.qt.io/qt-5.11/qtwebengine-features.html#audio-and-video-codecs

If you're using GNU/Linux, we recommend to use the flatpak as it comes with all the codecs needed.


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


There is a message saying that the browser is not supported or outdated. What can I do?
----------------------------------------------------------------------------

If you get the following (or similar) error message::

    You are trying to sign in from a browser or app that doesn't allow us to keep your account secure.
    Try using a different browser.

.. note:: The message might a bit different (e.g. on Yandex, the message say the browser is outdated).

You may want to try to `spoof your user agent`_  with the one from Firefox.

To change the user agent in MellowPlayer: **Settings -> Privacy -> User Agent**.

.. _spoof your user agent: https://help.vivaldi.com/article/user-agent-spoofing/


I have a warning about broken integration plugin. What can I do?
----------------------------------------------------------------

Since version 3.6.0, MellowPlayer tries to detect broken plugins and display a message to warn the user.

Here are the circumstances under which such a warning may appear:

- there are some unhandled exception in the intergation plugin.
- there is a known open issue on our issue tracker with the "broken integration plugin" label.
- [not yet implemented] the song information is empty but the web page is playing audio
