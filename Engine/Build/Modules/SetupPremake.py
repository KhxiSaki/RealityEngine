import os
from pathlib import Path
from Core import Logger
from Core.Utils import download_file, extract_zip, prompt_yes_no
import BuildConfig as Config

def validate() -> bool:
    """Validate Premake installation."""
    Logger.subheader("Premake")
    
    premake_exe = Path(Config.PREMAKE_DIR) / "premake5.exe"
    
    if premake_exe.exists():
        Logger.success(f"Premake found at {Config.PREMAKE_DIR}")
        return True
    
    Logger.warning("Premake not found")
    return _install()

def _install() -> bool:
    """Download and install Premake."""
    if not prompt_yes_no(f"Download Premake {Config.PREMAKE_VERSION}?"):
        return False
    
    zip_path = f"{Config.PREMAKE_DIR}/premake-{Config.PREMAKE_VERSION}.zip"
    
    Logger.info(f"Downloading Premake {Config.PREMAKE_VERSION}...")
    if not download_file(Config.PREMAKE_DOWNLOAD_URL, zip_path):
        return False
    
    Logger.info("Extracting...")
    if not extract_zip(zip_path):
        return False
    
    # Download license
    license_path = f"{Config.PREMAKE_DIR}/LICENSE.txt"
    download_file(Config.PREMAKE_LICENSE_URL, license_path, show_progress=False)
    
    Logger.success(f"Premake {Config.PREMAKE_VERSION} installed")
    return True

def get_executable() -> str:
    """Get path to Premake executable."""
    return os.path.abspath(f"{Config.PREMAKE_DIR}/premake5.exe")