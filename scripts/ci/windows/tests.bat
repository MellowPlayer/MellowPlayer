cd ..\..\..\build\tests

set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%

ctest --output-on-failure -C Release
