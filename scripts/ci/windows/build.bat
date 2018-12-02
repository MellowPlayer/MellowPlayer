cd ..\..\..
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..
cmake --build . --config Release
