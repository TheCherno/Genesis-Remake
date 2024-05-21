@echo off

:: See https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)

set PATH=%PATH%;C:\emsdk
call emsdk activate latest
mkdir Web
cd Web
call emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release
call emmake make

pause