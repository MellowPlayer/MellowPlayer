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


# Resources

- [Official website](https://colinduquesnoy.gitlab.io/MellowPlayer)
- [Documentation](http://mellowplayer.readthedocs.org/en/latest/)
- [Wiki](https://gitlab.com/ColinDuquesnoy/MellowPlayer/wikis/home)

# License

MellowPlayer is licensed under the GPL license.

# Requirements

## Build dependencies

- CMake >= 3.16
- a c++17 compiler (at least GCC 9 or msvc 2019)
- Qt5 >= 5.15.0:
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

- [Boost.DI](https://github.com/boost-ext/di)
- [spdlog](https://github.com/gabime/spdlog)
- [QHotkey](https://github.com/Skycoder42/QHotkey)

*These libraries will be fetched using CMake FetchContent if they are not available system wide*

### Testing

- [lcov](https://github.com/linux-test-project/lcov)
- [catch](https://github.com/catchorg/Catch2)

*Catch will always be fetched using Cmake FetchContent* 

# Compilation

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
- ``-DENABLE_QUICK_COMPILER``: Set this option to OFF to avoid using the Qt Quick Compiler. Default is ON.
- ``-DENABLE_QML_LINT``: Set this option to ON to use qmllint on all QML files. Default is OFF.


# Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://gitlab.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.md)!

