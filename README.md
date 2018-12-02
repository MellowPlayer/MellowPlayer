![MellowPlayer banner](docs/_static/banner.png)

[ ![Download](https://api.bintray.com/packages/colinduquesnoy/MellowPlayer/Stable/images/download.svg) ](https://bintray.com/colinduquesnoy/MellowPlayer/Stable/_latestVersion)
[![pipeline status](https://gitlab.com/ColinDuquesnoy/MellowPlayer/badges/master/pipeline.svg)](https://gitlab.com/ColinDuquesnoy/MellowPlayer/commits/master)
[![codecov](https://codecov.io/gl/ColinDuquesnoy/MellowPlayer/branch/master/graph/badge.svg)](https://codecov.io/gl/ColinDuquesnoy/MellowPlayer)
[![Join the chat at https://gitter.im/ColinDuquesnoy-MellowPlayer/Lobby](https://badges.gitter.im/ColinDuquesnoy-MellowPlayer/Lobby.svg)](https://gitter.im/ColinDuquesnoy-MellowPlayer/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

# About

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/)
*initially crafted for* [KaOS](http://kaosx.us/). *MellowPlayer is written in C++ and QML.*

# Supported services:

| Service                                                   | GNU/Linux | AppImage | Windows | Require non-free HTML codecs | Require  flash           | Require  drm |
|-----------------------------------------------------------|-----------|----------|---------|------------------------------|--------------------------|--------------|
| [Deezer](http://deezer.com)                               | Yes       | Yes      | Yes     | Yes (or flash)               | Yes (or non-free codecs) | No           |
| [Mixcloud](http://mixcloud.com)                           | Yes       | No       | No      | Yes                          | No                       | No           |
| [Soundcloud](http://soundcloud.com)                       | Yes       | No       | No      | Yes                          | No                       | No           |
| [Spotify](http://spotify.com)                             | Yes       | No       | No      | Yes                          | No                       | Yes          |
| [TuneIn](http://tunein.com/)                              | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [8tracks](http://8tracks.com/)                            | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [Google Play Music](https://play.google.com/music/listen) | Yes       | Yes      | Yes     | ?                            | ?                        | ?            |
| [Youtube](https://youtube.com/)                           | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [Tidal](https://listen.tidal.com/)                        | Yes       | Yes      | Yes     | No                           | Yes                      | No           |
| [Anghami](https://www.anghami.com/)                       | Yes       | No       | No      | Yes                          | No                       | No           |
| [Pocket Casts](https://play.pocketcasts.com/)             | Yes       | No       | No      | Yes                          | No                       | No           |
| [HearThisAt](https://hearthis.at/)                        | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [Jamendo](https://www.jamendo.com/start)                  | Yes       | Yes      | Yes     | No                           | No                       | No           |
| [Radionomy](https://www.radionomy.com/)                   | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [Wynk](https://www.wynk.in/music)                         | Yes       | No       | No      | Yes                          | No                       | No           |
| [ympd](https://github.com/notandy/ympd)                   | Yes       | Yes      | Yes     | No                           | No                       | No           |
| [Plex](https://www.plex.tv/)                              | Yes       | No       | No      | Yes                          | No                       | ?            |
| [Youtube Music](https://music.youtube.com/)               | Yes       | Yes      | Yes     | Depends on the stream        | No                       | No           |
| [Netflix](https://www.netflix.com)                        | Yes       | No       | No      | No                           | No                       | Yes          |

# Limitations:

- For licensing reason, we do not ship the flash player plugin and the widevine DRM plugins in our official releases.
- Some services (e.g. Spotify, Soundcloud and Mixcloud) also requires QtWebEngine to be compiled with proprietary codecs, which is not the case in our official releases.
- Tidal HiFi does not work because there is no MQA plugin available for chromium based browsers.

# Resources

- [Official website](https://colinduquesnoy.gitlab.io/MellowPlayer)
- [Documentation](http://mellowplayer.readthedocs.org/en/latest/)
- [Wiki on Github](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/home)

# License

MellowPlayer is licensed under the GPL license.

# Download

You can download official binaries from [BinTray](https://bintray.com/colinduquesnoy/MellowPlayer)

- [Stable](https://bintray.com/colinduquesnoy/MellowPlayer/Stable/_latestVersion)
- [Continuous](https://bintray.com/colinduquesnoy/MellowPlayer/Continuous/_latestVersion)



## GNU/Linux Packages

- [Fedora](http://mellowplayer.readthedocs.io/en/latest/users/install.html#fedora)
- [Ubuntu](http://mellowplayer.readthedocs.io/en/latest/users/install.html#ubuntu-17-10)
- [openSUSE](http://mellowplayer.readthedocs.io/en/latest/users/install.html#opensuse-tumbleweed)
- [ArchLinux](http://mellowplayer.readthedocs.io/en/latest/users/install.html#archlinux)
- [KaOS](http://mellowplayer.readthedocs.io/en/latest/users/install.html#kaos)

# Requirements

## Build dependencies

- CMake >= 3.10
- a c++17 compiler (gcc6, msvc 2015 or clang)
- Qt5 (>= 5.9.0, QtWebEngine and QtQuickControls2 needed)
- Libnotify (optional, GNU/Linux only)

## Bundled 3rd-parties

### Frameworks

- [Boost.DI](http://boost-experimental.github.io/di/)
- [spdlog](https://github.com/gabime/spdlog)
- [libqxt](https://bitbucket.org/libqxt/libqxt/wiki/Home) *(QxtGlobalShortcut)*

### Testing

- [catch](https://github.com/philsquared/Catch)
- [fakeit](https://github.com/eranpeer/FakeIt)
- [lcov](https://github.com/linux-test-project/lcov)

# Compilation

Building MellowPlayer requires [CMake](https://cmake.org/) >= 3.10 and a **C++17** compiler (GCC >= 6.x or Clang >= 3.5 or MSVC 2015 Update 2).

## From QtCreator

Open up `CMakeLists.txt` with QtCreator, hit build and run.

## From Command Line

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

#### Build options

You can append the following command line options when running cmake:

- ``-DBUILD_TESTS``: Set this option to ON to build tests. Default is OFF.
- ``-DDEFAULT_THEME``: Set this option to specify the default theme. Default is Adaptive.
- ``-DUSE_LD_GOLD``: Set this option to ON to use GNU Gold Linker. Default is ON.


# Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://gitlab.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.md)!

