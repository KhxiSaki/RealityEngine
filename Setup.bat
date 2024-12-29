@echo off
SETLOCAL

REM Check for administrative privileges
net session >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo This script requires administrative privileges. Attempting to run as administrator...
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

REM Define the URL for the CMake installer
set CMAKE_URL=https://github.com/Kitware/CMake/releases/download/v3.31.3/cmake-3.31.3-windows-x86_64.msi
set CMAKE_INSTALLER=cmake_installer.msi

REM Check if CMake is installed
where cmake >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    echo CMake is not installed. Downloading CMake...

    REM Download the CMake installer using curl if available, otherwise use PowerShell
    if exist "%ProgramFiles%\Git\mingw64\bin\curl.exe" (
        "%ProgramFiles%\Git\mingw64\bin\curl.exe" -L -o %CMAKE_INSTALLER% %CMAKE_URL%
    ) else (
        powershell -Command "Invoke-WebRequest -Uri %CMAKE_URL% -OutFile %CMAKE_INSTALLER%"
    )

    REM Check if the installer was downloaded successfully
    if not exist %CMAKE_INSTALLER% (
        echo Failed to download CMake. Please check your internet connection or the URL.
        pause
        exit /b 1
    )

    echo Installing CMake...
    msiexec /i %CMAKE_INSTALLER% /quiet /norestart /log install.log

    REM Check the exit code of msiexec
    IF %ERRORLEVEL% NEQ 0 (
        echo Failed to install CMake. Please check install.log for details.
        del %CMAKE_INSTALLER% 2>nul
        pause
        exit /b 1
    )

    echo CMake has been installed successfully.
    del %CMAKE_INSTALLER% 2>nul
) ELSE (
    echo CMake is already installed. Proceeding to generate Visual Studio files...
)

REM Call the GenerateVisualStudioFiles.bat script
call GenerateVisualStudioFiles.bat

ENDLOCAL