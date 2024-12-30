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

REM Define the URL for the ImGui docking branch
set IMGUI_URL=https://github.com/ocornut/imgui.git
set IMGUI_BRANCH=docking
set IMGUI_DIR=%~dp0Engine\ThirdParty\UI\imgui

REM Define the URL for the CoreCLR
set CORECLR_URL=https://github.com/dotnet/runtime
set CORECLR_DIR=%~dp0Engine\ThirdParty\CoreCLR

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

    REM Assume installation is successful
    echo CMake has been installed successfully.
    del %CMAKE_INSTALLER% 2>nul
) ELSE (
    echo CMake is already installed. Proceeding to generate Visual Studio files...
)

REM Check if ImGui directory exists
if not exist "%IMGUI_DIR%" (
    echo ImGui not found. Downloading ImGui...

    REM Create the directory for ImGui
    mkdir "%IMGUI_DIR%"

    REM Download ImGui docking branch using git if available, otherwise use PowerShell to clone
    if exist "%ProgramFiles%\Git\cmd\git.exe" (
        pushd "%IMGUI_DIR%"
        "%ProgramFiles%\Git\cmd\git.exe" clone --recursive -b %IMGUI_BRANCH% %IMGUI_URL% .
        popd
    ) else (
        echo Git is not installed. Please install Git to download ImGui.
        pause
        exit /b 1
    )

    echo ImGui docking branch has been downloaded successfully.
) ELSE (
    echo ImGui is already downloaded. Proceeding...
)

REM Check if CoreCLR directory exists
if not exist "%CORECLR_DIR%" (
    echo CoreCLR not found. Downloading CoreCLR...

    REM Create the directory for CoreCLR
    mkdir "%CORECLR_DIR%"

    REM Download CoreCLR using git if available, otherwise use PowerShell to clone
    if exist "%ProgramFiles%\Git\cmd\git.exe" (
        pushd "%CORECLR_DIR%"
        "%ProgramFiles%\Git\cmd\git.exe" clone --recursive "%CORECLR_URL%" .
        popd
    ) else (
        echo Git is not installed. Please install Git to download CoreCLR.
        pause
        exit /b 1
    )

    echo CoreCLR has been downloaded successfully.
) ELSE (
    echo CoreCLR is already downloaded. Proceeding...
)


PAUSE
ENDLOCAL