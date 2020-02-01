cd ..\..\..

git rev-list HEAD --count > build_number.txt
set /p build_number=<build_number.txt

curl -T .\MellowPlayer_Setup.exe -ucolinduquesnoy:%BINTRAY_API_KEY% "https://api.bintray.com/content/colinduquesnoy/MellowPlayer/Stable/%APP_VERSION%.%build_number%/stable/%APP_VERSION%.%build_number%/MellowPlayer_Setup.exe?publish=1&override=1&explode=0"
