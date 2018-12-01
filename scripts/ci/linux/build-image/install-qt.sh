#!/usr/bin/env bash
COMPILER_TYPE=gcc_64
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=11
QT_VERSION_PATCH=2
QT_VERSION="${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}"
QT_COMPONENT_VERSION=${QT_VERSION_MAJOR}.${QT_VERSION_MAJOR}${QT_VERSION_MINOR}${QT_VERSION_PATCH}
QT_INSTALL_DIR=/opt/qt
INSTALLER=$PWD/qt-opensource-linux-x64-${QT_VERSION}.run

wget https://download.qt.io/archive/qt/${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run

export QT_CI_PACKAGES=qt.qt${QT_COMPONENT_VERSION}.${COMPILER_TYPE},qt.qt${QT_COMPONENT_VERSION}.qtwebengine,qt.tools.qtcreator
chmod +x ./extract-qt-installer
./extract-qt-installer $INSTALLER ${QT_INSTALL_DIR}
rm -f $INSTALLER
