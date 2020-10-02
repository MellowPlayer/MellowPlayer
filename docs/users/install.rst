Installation
============

This page will guide you throught the installation of MellowPlayer on the
supported operating systems.

GNU/Linux
---------

We provide several ways to install a pre-compiled version of MellowPlayer on GNU/Linux:

1. Flatpak
2. Native packages

**Flatpak is the recommended solution** as it is what the developers use and test against. It contains a recent version
of QtWebEngine/Chromium which is essential for MellowPlayer to work correctly.

Native packages (especially on old/LTS distributions) may cause problems as they don't provide a recent version of QtWebEngine/Chromium

Flatpak
+++++++

MellowPlayer is available on `flathub`_:

.. code-block:: bash

    flatpak install flathub com.gitlab.ColinDuquesnoy.MellowPlayer


.. _flathub: https://flathub.org/apps/details/com.gitlab.ColinDuquesnoy.MellowPlayer

Native Packages
+++++++++++++++

Fedora
~~~~~~

Starting from Fedora 27, MellowPlayer is available from the official stable repositories:

.. code-block:: bash

    sudo dnf install mellowplayer

Most services require proprietary audio codecs to work. You can install them from the `RPMFusion repositories`_:

.. code-block:: bash

    sudo dnf install qt5-qtwebengine-freeworld

ArchLinux
~~~~~~~~~

MellowPlayer is available from the `AUR`_, install it with your favorite AUR tool (e.g. yaourt).


.. code-block:: bash

    yaourt -S mellowplayer

.. _AUR: https://aur.archlinux.org/packages/mellowplayer

KaOS
~~~~

MellowPlayer is available from `KaOSx/apps`_ repository, just run:

.. code-block:: bash

    $ sudo pacman -S mellowplayer


.. _KaOSx/apps: https://kaosx.us/packages/packages.php?sortby=name&sortdir=&flagged=&page=&repo=apps&exact=&search=mellowplayer

Other distributions
~~~~~~~~~~~~~~~~~~~

Pre-compiled packages for other distributions (Ubuntu, openSUSE,...) can be found on our `OBS Download Page`_

.. _OBS Download Page: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=mellowplayer

Compiling from source
+++++++++++++++++++++

See the `README`_ for build instructions.

.. _README: https://gitlab.com/ColinDuquesnoy/MellowPlayer/blob/master/README.md#compilation

Widevine DRM Plugin
+++++++++++++++++++

Many services like Spotify, Tidal and Amazon Music require the widevine DRM plugin to work.

You can install it on GNU/Linux by running the below script (tested with native packages and flatpak; make sure the `binutils` package is installed on Debian/Ubuntu providing the `ar` command)

.. code-block:: bash

    curl -s "https://gitlab.com/ColinDuquesnoy/MellowPlayer/-/raw/master/scripts/install-widevine.sh" | bash


Windows
-------

Just grab the windows installer from the `official website`_ (click on the **Windows folder**) and follow the instructions.

Please note the Windows Installer we provide is built with a version of QtWebEngine built without proprietary codecs support (for licensing reasons).
If your favorite service require proprietary codecs to work, you'll need to build QtWebEngine with the flag ``use_proprietary_codecs`` and build MellowPlayer using that QtWebEngine version.


.. _official website: https://colinduquesnoy.gitlab.io/MellowPlayer
.. _RPMFusion repositories: https://rpmfusion.org/Configuration

OS X
----

OSX is not officially supported anymore. You may try to build and run MellowPlayer from sources.
