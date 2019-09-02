#!/usr/bin/env bash
# For Ubuntu >= 19.04

packages=(
  # Build tools
  build-essential
  cmake
  ninja-build

  # Qt Development packages
  qt5-qmake
  qt5-default
  qtbase5-dev
  qtbase5-private-dev
  qttools5-dev
  qttools5-dev-tools
  qtdeclarative5-dev
  qtdeclarative5-private-dev
  qtwebengine5-dev
  libqt5svg5-dev
  libqt5websockets5-dev
  qttranslations5-l10n
  qtquickcontrols2-5-dev
  qml-module-qtquick2
  qml-module-qtquick-controls
  qml-module-qtquick-controls2
  qml-module-qtquick-dialogs
  qml-module-qtquick-extras
  qml-module-qtquick-layouts
  qml-module-qtquick-privatewidgets
  qml-module-qtquick-templates2
  qml-module-qtquick-window2
  qml-module-qtwebengine
  qml-module-qtwebchannel
  qml-module-qt-labs-platform
  qml-module-qtqml-models2
  qml-module-qt-labs-settings
  qml-module-qt-labs-folderlistmodel

  # Other dependencies
  libspdlog-dev
  libgtest-dev

  # Codecs
  libavcodec-extra

  # libnotify
  libnotify-dev

  # Backward dependencies
  libdw-dev
  libbfd-dev
  libdwarf-dev
)
sudo apt -y install ${packages[@]}
