@echo off
setlocal

mkdir Build
cd Build
cmake -Wno-dev -G "Visual Studio 14 2015 Win64" ..

endlocal

pause
