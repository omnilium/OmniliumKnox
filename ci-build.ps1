New-Item -ItemType directory -Path ./ci-build
Set-Location ./ci-build/
cmake .. -DCMAKE_BUILD_TYPE:STRING="Release"
cmake --build . --config Release
New-Item -ItemType directory -Path ./artifacts
Copy-Item -Path ./Core/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False
Copy-Item -Path ./KnoxC/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False
Copy-Item -Path ./Knox/Release/* -Destination ./artifacts -PassThru -Recurse -Force -Confirm:$False