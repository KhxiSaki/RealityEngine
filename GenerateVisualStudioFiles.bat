@echo off

REM Set the build directory
set BUILD_DIR=Build

REM Create the build directory if it doesn't exist
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

REM Navigate to the build directory
cd "%BUILD_DIR%"

REM Run CMake to generate Visual Studio project files
cmake .. -G "Visual Studio 17 2022"

REM Check for errors in the CMake command
if %ERRORLEVEL% NEQ 0 (
    echo CMake failed. Please check the output for errors.
    pause
    exit /b %ERRORLEVEL%
)

echo Visual Studio project files generated successfully.
pause