![MellowPlayer banner](docs/_static/banner.png)

[![Flathub](https://img.shields.io/flathub/v/com.gitlab.ColinDuquesnoy.MellowPlayer)](https://flathub.org/apps/details/com.gitlab.ColinDuquesnoy.MellowPlayer)
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

See the [list of supported services](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/Supported-Services) on our wiki.

# Limitations:

- For licensing reason, we do not ship the flash player plugin and the widevine DRM plugins in our official releases.
- Some services (e.g. Spotify, Soundcloud and Mixcloud) also requires QtWebEngine to be compiled with proprietary codecs, which is not the case in our official releases.
- Tidal HiFi does not work because there is no MQA plugin available for chromium based browsers.

# Resources

- [Official website](https://colinduquesnoy.gitlab.io/MellowPlayer)
- [Documentation](http://mellowplayer.readthedocs.org/en/latest/)
- [Wiki on GitLab](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/home)

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
- Qt5 >= 5.9.0:
  - QtConcurrent
  - QtDBus
  - QtLinguisticTools
  - QtQuickControls2
  - QtSql
  - QtSvg
  - QtWebEngine compiled with Widget support
- Libnotify (optional, GNU/Linux only)

## Bundled 3rd-parties

### Frameworks

- [Boost.DI](http://boost-experimental.github.io/di/)
- [spdlog](https://github.com/gabime/spdlog)
- [libqxt](https://bitbucket.org/libqxt/libqxt/wiki/Home) *(QxtGlobalShortcut)*

### Testing

- [catch](https://github.com/philsquared/Catch)
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

