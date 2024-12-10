@echo off
pushd %~dp0\..\
call Engine\Build\premake\bin\premake5.exe vs2022
popd
PAUSE
