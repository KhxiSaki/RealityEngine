@echo off
pushd %~dp0
call Engine\Binaries\Premake\premake5.exe vs2022
popd
PAUSE