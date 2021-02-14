$ErrorActionPreference = 'Stop'

$SONAR_PROJECT_KEY="omnilium_OmniliumKnox"
$SONAR_PROJECT_NAME="OmniliumKnox"
$SONAR_ORGANIZATION="omnilium"

$SONAR_URL = If ( $SONAR_URL ) { $SONAR_URL } else {"https://sonarcloud.io"}

mkdir $HOME/.sonar
$SONAR_SCANNER_VERSION = "4.5.0.2216"
$SONAR_SCANNER_HOME = "$HOME/.sonar/sonar-scanner-$SONAR_SCANNER_VERSION-windows"

$path = "$HOME/.sonar/build-wrapper-win-x86.zip"
rm build-wrapper-win-x86 -Recurse -Force -ErrorAction SilentlyContinue
rm $path -Force -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
(New-Object System.Net.WebClient).DownloadFile("$SONAR_URL/static/cpp/build-wrapper-win-x86.zip", $path)
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::ExtractToDirectory($path, "$HOME/.sonar")
$env:Path += ";$HOME/.sonar/build-wrapper-win-x86"

$path = "$HOME/.sonar/sonar-scanner-cli-$SONAR_SCANNER_VERSION-windows.zip"
rm sonar-scanner -Recurse -Force -ErrorAction SilentlyContinue
rm $path -Force -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
(New-Object System.Net.WebClient).DownloadFile("https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-windows.zip", $path)
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::ExtractToDirectory($path, "$HOME/.sonar")
$env:Path += ";$SONAR_SCANNER_HOME\bin"

New-Item -ItemType directory -Path ./out
Set-Location ./out/
cmake .. -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="artifact/"

build-wrapper-win-x86-64 --out-dir sonar cmake --build . --config Release

sonar-scanner -D sonar.host.url=$SONAR_URL -D sonar.projectKey=${SONAR_ORGANIZATION}:${SONAR_PROJECT_KEY} -D sonar.organization=$SONAR_ORGANIZATION -D sonar.projectName=OmniliumKnox -D sonar.projectVersion=$BUILD_VERSION -D sonar.sourceEncoding=UTF-8
