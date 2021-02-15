$ErrorActionPreference = 'Stop'

$SONAR_PROJECT_KEY="omnilium_OmniliumKnox"
$SONAR_PROJECT_NAME="OmniliumKnox"
$SONAR_ORGANIZATION="omnilium"

$SONAR_URL = If ( $SONAR_URL ) { $SONAR_URL } else {"https://sonarcloud.io"}

if (Test-Path $HOME/.sonar) {
    Remove-Item $HOME/.sonar -Force -Recurse -ErrorAction SilentlyContinue
}
New-Item -ItemType directory -Path $HOME/.sonar
$SONAR_SCANNER_VERSION = "4.5.0.2216"
$SONAR_SCANNER_HOME = "$HOME/.sonar/sonar-scanner-$SONAR_SCANNER_VERSION-windows"

$path = "$HOME/.sonar/build-wrapper-win-x86.zip"
Remove-Item build-wrapper-win-x86 -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item $path -Force -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
(New-Object System.Net.WebClient).DownloadFile("$SONAR_URL/static/cpp/build-wrapper-win-x86.zip", $path)
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::ExtractToDirectory($path, "$HOME/.sonar")
$env:Path += ";$HOME/.sonar/build-wrapper-win-x86"

$path = "$HOME/.sonar/sonar-scanner-cli-$SONAR_SCANNER_VERSION-windows.zip"
Remove-Item sonar-scanner -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item $path -Force -ErrorAction SilentlyContinue
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
(New-Object System.Net.WebClient).DownloadFile("https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-$SONAR_SCANNER_VERSION-windows.zip", $path)
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::ExtractToDirectory($path, "$HOME/.sonar")
$env:Path += ";$SONAR_SCANNER_HOME\bin"

if (Test-Path ./sonar) {
    Remove-Item ./sonar -Force -Recurse -ErrorAction SilentlyContinue
}
New-Item -ItemType directory -Path ./sonar
Set-Location ./sonar/

cmake .. -DCMAKE_BUILD_TYPE:STRING="Release"
build-wrapper-win-x86-64 --out-dir sonar-analysis cmake --build . --config Release
cmake --install . --config Release --prefix install

Set-Location ../
sonar-scanner -D sonar.login=$SONAR_TOKEN -D sonar.host.url=$SONAR_URL -D sonar.projectKey=${SONAR_PROJECT_KEY} -D sonar.organization=$SONAR_ORGANIZATION -D sonar.projectName=OmniliumKnox -D sonar.projectVersion=$BUILD_VERSION -D sonar.sourceEncoding=UTF-8 -D sonar.sources=. -D sonar.cfamily.build-wrapper-output=sonar/sonar-analysis -D sonar.cfamily.threads=1 -D  sonar.cfamily.cache.enabled=true -D sonar.cfamily.cache.path=sonar-cache
