@echo off
pushd %~dp0

python Engine/Build/GenerateProjectFiles.py %*

popd
if "%1" neq "nopause" pause