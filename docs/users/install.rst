Installation
============

This page will guide you throught the installation of MellowPlayer on the
supported operating systems.

GNU/Linux
---------

We provide several ways to install a pre-compiled version of MellowPlayer on GNU/Linux:

1. Native package
2. Flatpak
3. AppImage

To choose which kind of installer you should use, follow those simple rules:

- Always prefer the native package to any other format if that is available for your distribution. Native package will always integrate better with your desktop and, in most cases, it will pick up proprietary codecs (ffmpeg) from your system if installed.
- Prefer flatpak over AppImage, especially if the service you want to use require proprietary audio codecs.
- Use the AppImage if flatpak is not available on your distribution (very unlikely) and you don't need proprietary codecs.

Fedora
++++++

Starting from Fedora 27, MellowPlayer is available from the official stable repositories:

.. code-block:: bash

    sudo dnf install mellowplayer

Proprietary codecs
******************

Most services require proprietary audio codecs to work. You can install them from the `RPMFusion repositories`_:

.. code-block:: bash

    sudo dnf install qt5-qtwebengine-freeworld

Widevine
********

Some services such as Spotify and Amazon Music requires the widevine ppapi plugin to work, you can install it by running the below commands:

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

.. note:: You might need to adapt this script to download a version of chromium and widevine that match the version used by your Qt installation.

ArchLinux
+++++++++

MellowPlayer is available from the `AUR`_, install it with your favorite AUR tool (e.g. yaourt).


.. code-block:: bash

    yaourt -S mellowplayer

.. _AUR: https://aur.archlinux.org/packages/mellowplayer

KaOS
++++

MellowPlayer is available from `KaOSx/apps`_ repository, just run:

.. code-block:: bash

    $ sudo pacman -S mellowplayer


.. _KaOSx/apps: https://kaosx.us/packages/packages.php?sortby=name&sortdir=&flagged=&page=&repo=apps&exact=&search=mellowplayer

Other distributions
++++++++++++++++++++

Pre-compiled packages for other distributions (Ubuntu, openSUSE,...) can be found on our `OBS Download Page`_

.. _OBS Download Page: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=mellowplayer

Flatpak
+++++++

MellowPlayer's flatpak is not yet available on flathub but you can download and install a single file bundle:

1. Download the flatpak from our `bintray repository`_
2. Install the flatpak: ``flatpak install ./MellowPlayer.flatpak``
3. Run the flatpak from your application menu or from command line: ``flatpak run com.gitlab.ColinDuquesnoy.MellowPlayer``


AppImage
++++++++

1. Download the AppImage from our `bintray repository`_
2. Make it executable: ``chmod +x ./MellowPlayer.AppImage``
3. Run it: ``./MellowPlayer.AppImage``

.. _bintray repository: https://bintray.com/colinduquesnoy/MellowPlayer/Stable

Compiling from source
+++++++++++++++++++++

See the `README`_ for build instructions.

.. _README: https://gitlab.com/ColinDuquesnoy/MellowPlayer/blob/master/README.md#compilation

Windows
-------

Just grab the windows installer from the `official website`_ (click on the **Windows folder**) and follow the instructions.

Please note the Windows Installer we provide is built with a version of QtWebEngine built without proprietary codecs support (for licensing reasons).
If your favorite service require proprietary codecs to work, you'll need to build QtWebEngine with the flag ``use_proprietary_codecs`` and build MellowPlayer using that QtWebEngine version.


.. _official website: https://colinduquesnoy.gitlab.io/MellowPlayer
.. _openSUSE build service: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=MellowPlayer
.. _RPMFusion repositories: https://rpmfusion.org/Configuration

OS X
----

OSX is not officially supported anymore. You may try to build and run MellowPlayer from sources.
