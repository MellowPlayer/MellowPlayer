cd ..\..\..

curl -T MellowPlayer_Setup.exe -ucolinduquesnoy:%BINTRAY_API_KEY% "https://api.bintray.com/content/colinduquesnoy/MellowPlayer/Continuous/%APPVEYOR_BUILD_VERSION%/continuous/%APPVEYOR_BUILD_VERSION%/MellowPlayer_Setup.exe?publish=1&override=1&explode=0"

