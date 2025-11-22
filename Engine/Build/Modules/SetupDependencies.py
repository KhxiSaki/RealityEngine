import os
import shutil
from pathlib import Path
from Core import Logger
from Core.Utils import download_file, extract_zip
import BuildConfig as Config

def validate() -> bool:
    """Validate and install all dependencies."""
    Logger.subheader("Third-Party Dependencies")
    
    if not Config.DEPENDENCIES:
        Logger.info("No dependencies configured")
        return True
    
    all_ok = True
    for dep in Config.DEPENDENCIES:
        if not _check_dependency(dep):
            all_ok = False
    
    return all_ok

def _check_dependency(dep: Config.Dependency) -> bool:
    """Check if a dependency is installed, install if missing."""
    install_path = Path(dep.install_path)
    
    if install_path.exists():
        Logger.success(f"{dep.name} ({dep.version}) found")
        return True
    
    Logger.info(f"Installing {dep.name} ({dep.version})...")
    return _install_dependency(dep)

def _install_dependency(dep: Config.Dependency) -> bool:
    """Download and install a dependency."""
    zip_path = f"{dep.install_path}.zip"
    
    if not download_file(dep.url, zip_path):
        Logger.error(f"Failed to download {dep.name}")
        return False
    
    if not extract_zip(zip_path):
        Logger.error(f"Failed to extract {dep.name}")
        return False
    
    # Move from extracted folder to install path if needed
    if dep.extracted_folder:
        extracted = Path(dep.install_path).parent / dep.extracted_folder
        if extracted.exists():
            shutil.move(str(extracted), dep.install_path)
    
    Logger.success(f"{dep.name} installed")
    return True