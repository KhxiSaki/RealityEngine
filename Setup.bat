@echo off
pushd %~dp0

where python >nul 2>nul
if %errorlevel% neq 0 (
    echo Python is not installed or not in PATH!
    echo Please install Python 3.14 or higher from https://python.org
    pause
    exit /b 1
)

python Engine/Build/Setup.py %*

popd
if "%1" neq "nopause" pause