cd ..\..\..
echo "QTDIR=%QTDIR%"
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..
cmake --build . --config Release