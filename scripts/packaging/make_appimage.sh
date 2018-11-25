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
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage

# Build MellowPlayer and link statically git libstdc++
mkdir -p build
mkdir -p appdir
pushd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=FALSE -DSTATIC_LIBSTDCPP=TRUE ..
make -j$(nproc)
make DESTDIR=../appdir install
popd

# create appdir
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -exclude-libs="libnss3.so,libnssutil3.so" -bundle-non-qt-libs -qmldir=src/lib/presentation/imports/MellowPlayer -verbose=2

# copy missing qml files
echo "Copying missing files..."
cp ${QT_DIR}/plugins/imageformats/libqsvg.so ./appdir/usr/plugins/imageformats/
mkdir -p ./appdir/usr/qml
cp -R ${QT_DIR}/qml ./appdir/usr/qml
cp -R /usr/share/qt5 ./appdir/usr
echo "ls /usr/share/qt5/resources"
ls /usr/share/qt5/resources
ls ./appdir/usr/resources

# create appimage
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -exclude-libs="libnss3.so,libnssutil3.so" -appimage
chmod +x MellowPlayer-x86_64.AppImage
