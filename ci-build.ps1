New-Item -ItemType directory -Path ./ci-build
Set-Location ./ci-build/
cmake .. -DCMAKE_BUILD_TYPE:STRING="Release"
cmake --build . --config Release
New-Item -ItemType directory -Path ./artifacts

$Exclude = @("*.exp", "*.lib")
Copy-Item -Path ./core/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False -Exclude $Exclude
Copy-Item -Path ./knoxcli/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False -Exclude $Exclude
Copy-Item -Path ./knox/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False -Exclude $Exclude