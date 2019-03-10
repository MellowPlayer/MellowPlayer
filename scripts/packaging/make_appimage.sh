#!/usr/bin/env bash
#
# This script takes one argument: the path to the qt installation directory.
#
# This script should be run from the root source directory:
#
#   ./scripts/packaging/make_appimage.sh PATH_TO_QT_INSTALL_DIR
#
# E.g., on openSUSE: ./scripts/packaging/make_appimage.sh /usr/lib64/qt5
#

# override path so that the correct qmake version is used
QT_DIR=$1
QMAKE_PATH=${QT_DIR}/bin
PATH=${QMAKE_PATH}:$PATH
export LD_LIBRARY_PATH=${QT_DIR}/lib
echo "checking qmake"
qmake -v

# download linuxdployqt
echo "downloading linuxdeployqt"
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/6/linuxdeployqt-6-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage

# create appdir
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -exclude-libs="libnss3.so,libnssutil3.so" -bundle-non-qt-libs -qmldir=src/lib/presentation/imports/MellowPlayer -verbose=2

# copy missing qml files
echo "Copying missing files..."
cp ${QT_DIR}/plugins/imageformats/libqsvg.so ./appdir/usr/plugins/imageformats/

# create appimage
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -exclude-libs="libnss3.so,libnssutil3.so" -appimage -verbose=2
mv MellowPlayer-*-x86_64.AppImage MellowPlayer-x86_64.AppImage
chmod +x MellowPlayer-x86_64.AppImage
