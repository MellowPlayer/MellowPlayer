cd ..\..\..\build\src\tests

set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%

ctest -C Release
