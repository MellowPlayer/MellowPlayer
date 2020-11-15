BUILD_DIR=$PWD/../cmake-build-debug
SRC_DIR=$PWD/../src

cd $BUILD_DIR/src/lib/presentation


mkdir -p qml/MellowPlayer
cp libMellowPlayer.Presentation.so qml/MellowPlayer
echo "module MellowPlayer
plugin MellowPlayer.Presentation
classname MellowPlayerQmlPlugin
" > qml/MellowPlayer/qmldir

qmlplugindump -v -qapp MellowPlayer 3.0 $PWD/qml > $SRC_DIR/lib/presentation/imports/MellowPlayer/cpp.qmltypes
