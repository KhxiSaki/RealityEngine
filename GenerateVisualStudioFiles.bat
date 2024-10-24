@echo off
:: Navigate to the RealityEngine directory
cd /d "C:\RealityEngine"

:: Ensure the Premake5 executable path is accessible
if exist "Engine\Build\premake5.exe" (
    echo Generating Visual Studio project files...
    "Engine\Build\premake5.exe" vs2022
    pause
) else (
    echo Error: premake5.exe not found in Engine\Build directory!
    pause
)