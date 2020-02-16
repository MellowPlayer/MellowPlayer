$url = $Args[0]
$destination = $Args[1]
$downloadedFile = "$env:TEMP\mellowplayer-connect.zip"

Write-Host "Url: " + $url
Write-Host "Output: " + $downloadedFile
Write-Host "Destination: " + $destination

(New-Object System.Net.WebClient).DownloadFile($url, $downloadedFile)
Expand-Archive -Path $downloadedFile -DestinationPath $destination -Force
