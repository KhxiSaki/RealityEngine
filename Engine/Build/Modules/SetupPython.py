import sys
import subprocess
import importlib.util
from Core import Logger
import BuildConfig as Config

def validate() -> bool:
    """Validate Python version and required packages."""
    Logger.subheader("Python Environment")
    
    if not _check_version():
        return False
    
    for package in Config.PYTHON_PACKAGES:
        if not _check_package(package):
            return False
    
    return True

def _check_version() -> bool:
    """Check if Python version meets requirements."""
    major, minor = Config.PYTHON_VERSION_MIN
    current = sys.version_info
    
    Logger.info(f"Python {current.major}.{current.minor}.{current.micro} detected")
    
    if current.major < major or (current.major == major and current.minor < minor):
        Logger.error(f"Python {major}.{minor}+ required")
        return False
    
    Logger.success("Python version OK")
    return True

def _check_package(name: str) -> bool:
    """Check if a package is installed, install if missing."""
    if importlib.util.find_spec(name) is not None:
        Logger.success(f"Package '{name}' found")
        return True
    
    Logger.warning(f"Package '{name}' not found")
    
    from Core.Utils import prompt_yes_no
    if not prompt_yes_no(f"Install '{name}'?"):
        return False
    
    try:
        subprocess.check_call([sys.executable, '-m', 'pip', 'install', name], 
                            stdout=subprocess.DEVNULL)
        Logger.success(f"Package '{name}' installed")
        return True
    except subprocess.CalledProcessError:
        Logger.error(f"Failed to install '{name}'")
        return False