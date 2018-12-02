cd ..\..\..

curl -T .\MellowPlayer_Setup.exe -ucolinduquesnoy:%BINTRAY_API_KEY% "https://api.bintray.com/content/colinduquesnoy/MellowPlayer/Stable/%APPVEYOR_BUILD_VERSION%/stable/%APPVEYOR_BUILD_VERSION%/MellowPlayer_Setup.exe?publish=1&override=1&explode=0"
