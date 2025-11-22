import os
from pathlib import Path
from Core import Logger
from Core.Utils import download_file, prompt_yes_no
import BuildConfig as Config

def validate() -> bool:
    """Validate Vulkan SDK installation."""
    Logger.subheader("Vulkan SDK")
    
    vulkan_sdk = os.environ.get("VULKAN_SDK")
    
    if vulkan_sdk is None:
        Logger.warning("Vulkan SDK not found in environment")
        _prompt_install()
        return False
    
    if Config.VULKAN_VERSION_REQUIRED not in vulkan_sdk:
        Logger.warning(f"Vulkan SDK version mismatch (need {Config.VULKAN_VERSION_REQUIRED})")
        _prompt_install()
        return False
    
    Logger.success(f"Vulkan SDK found at {vulkan_sdk}")
    
    # Check debug libs
    if not _check_debug_libs(vulkan_sdk):
        Logger.warning("Debug libs not found - Debug builds may not work")
    else:
        Logger.success("Debug libraries found")
    
    return True

def _check_debug_libs(sdk_path: str) -> bool:
    """Check if Vulkan debug libraries are installed."""
    debug_lib = Path(sdk_path) / "Lib" / "shaderc_sharedd.lib"
    return debug_lib.exists()

def _prompt_install() -> None:
    """Prompt to download and run Vulkan SDK installer."""
    if not prompt_yes_no(f"Download Vulkan SDK {Config.VULKAN_VERSION_INSTALL}?"):
        return
    
    installer_path = f"{Config.VULKAN_SDK_DIR}/VulkanSDK-{Config.VULKAN_VERSION_INSTALL}-Installer.exe"
    
    Logger.info(f"Downloading Vulkan SDK {Config.VULKAN_VERSION_INSTALL}...")
    if not download_file(Config.VULKAN_DOWNLOAD_URL, installer_path):
        return
    
    Logger.info("Launching installer...")
    os.startfile(os.path.abspath(installer_path))
    Logger.warning("Please re-run Setup after Vulkan installation completes!")