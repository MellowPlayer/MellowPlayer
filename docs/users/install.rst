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

Widevine Support
++++++++++++++++

Some services such as Spotify and Amazon Music requires the widevine ppapi plugin to work, you can install it by running the below script (Tested on Ubuntu 20.04):

.. code-block:: bash

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

Widevine support in flatpak
***************************

Flatpak won't pick up the system widevine plugin. It must be moved to a place that can be accessed from flatpak (e.g. ``~/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/``) and
you must instruct QtWebEngine where to find the plugin (using a flatpak override):

.. code-block:: bash

    mkdir -p ~/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi
    cp /usr/lib/chromium/libwidevinecdm.so ~/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi/
    sudo flatpak override --env=QTWEBENGINE_CHROMIUM_FLAGS="--widevine-path=$HOME/.var/app/com.gitlab.ColinDuquesnoy.MellowPlayer/plugins/ppapi/libwidevinecdm.so --no-sandbox" com.gitlab.ColinDuquesnoy.MellowPlayer

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
