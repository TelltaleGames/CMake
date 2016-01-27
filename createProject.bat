@echo off
setlocal

mkdir Build
cd Build
cmake -Wno-dev -G "Visual Studio 10" ..

endlocal

pause
