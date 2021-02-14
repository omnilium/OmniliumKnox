Remove-Item ./sln -Recurse
New-Item -ItemType directory -Path ./sln
Set-Location ./sln/
cmake .. -G "Visual Studio 16 2019" -A x64