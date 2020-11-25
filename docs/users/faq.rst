FAQ & Known issues
==================

Playback does not start on some services... What can I do?
----------------------------------------------------------

For many services to work, QtWebEngine/chromium needs to be **compiled** with `support for proprietary Audio/Video codecs`_ support (off by default in official pre-compiled Qt binaries)
If you have playback issues on GNU/Linux, we recommend to use `our flatpak`_ (which comes with all necessary codecs) instead of the native package or the AppImage.

Additionally, many services (Spotify, Tidal, Netflix, Amazon Music,...) use DRM and you **MUST** `install the widevine DRM plugin`_.

.. _support for proprietary Audio/Video codecs: https://doc.qt.io/qt-5/qtwebengine-features.html#audio-and-video-codecs
.. _install the widevine DRM plugin: https://mellowplayer.readthedocs.io/en/latest/users/install.html#widevine-drm-plugin

Some services are not listed on Windows, is that normal?
--------------------------------------------------------

Yes. The windows version of MellowPlayer is built with the official pre-compiled Qt binaries wich is built without proprietary codecs. Services that requires proprietary
codecs are blacklisted on Windows becauouse they wouldn't work with our binary distribution anyway.

To workaround the isseu, try the following steps:

1. Edit the plugin metadata file ($INSTALL_DIR/plugins/PLUGIN_NAME/metadata.ini) and change the ``support_platform`` value to ``All`` instead of ``Linux``
2. Recompile QtWebEngine from source and make sure to enable proprietary codecs support
3. Replace the QtWebEngine dll supplied by the MellowPlayer installer by the one you just built (or recompile MellowPlayer from source using your own version of Qt)
4. If the service require DRM, try to find the widevinecdm dll in your google chrom installation and copy it next to the MellowPlayer executable.

.. note:: We never tried the above mentioned steps as most of us are not Windows users. Your contribution is welcome!

The application crashes at startup on GNU/Linux with open source NVIDIA drivers. What can I do?
-----------------------------------------------------------------------------------------------

Qt/QML applications don't work well with the open source NVIDIA drivers (nouveau). It is recommended to **use the proprietary NVIDIA drivers**.

The application crashes at startup on GNU/Linux with proprietary NVIDIA drivers. What can I do?
-----------------------------------------------------------------------------------------------

Make sure you rebooted after your last NVIDIA driver update and make sure to run ``sudo nvidia-xconfig`` before reporting the issue.

There is a message saying that the browser is not supported or outdated. What can I do?
---------------------------------------------------------------------------------------

If you get the following (or similar) error message::

    You are trying to sign in from a browser or app that doesn't allow us to keep your account secure.
    Try using a different browser.

.. note:: The message might a bit different (e.g. on Yandex, the message say the browser is outdated).

You may want to try to `spoof your user agent`_  with the one from Firefox.

To change the user agent in MellowPlayer: **Settings -> Privacy -> User Agent**.

.. _spoof your user agent: https://help.vivaldi.com/article/user-agent-spoofing/


My login credentials are lost or refused. What can I do?
--------------------------------------------------------

If you're using a native version of MellowPlayer on an old distribution or our AppImage chances are the Qt (especially QtWebEngine/chromium) version is too
old is not supported by the service you try to log in.

Use our flatpak instead.

I have a warning about broken integration plugin. What can I do?
----------------------------------------------------------------

Since version 3.6.0, MellowPlayer tries to detect broken plugins and display a message to warn the user.

Here are the circumstances under which such a warning may appear:

- there are some unhandled exception in the intergation plugin.
- there is a known open issue on our issue tracker with the "broken integration plugin" label.
- [not yet implemented] the song information is empty but the web page is playing audio
