cd ..\..\..

curl -T .\MellowPlayer_Setup.exe -ucolinduquesnoy:%BINTRAY_API_KEY% "https://api.bintray.com/content/colinduquesnoy/MellowPlayer/Stable/%APP_VERSION%/stable/%APP_VERSION%/MellowPlayer_Setup.exe?publish=1&override=1&explode=0"
