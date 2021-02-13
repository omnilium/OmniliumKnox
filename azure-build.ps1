New-Item -ItemType directory -Path ./out
Set-Location ./out/
cmake .. -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="artifact/"
cmake --build . --config Release
New-Item -ItemType directory -Path ./artifacts
Copy-Item -Path ./Core/Release/* -Destination ./artifacts -PassThru -Recurse
Copy-Item -Path ./KnoxC/Release/* -Destination ./artifacts -PassThru -Recurse
Copy-Item -Path ./Knox/Release/* -Destination ./artifacts -PassThru -Recurse