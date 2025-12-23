import os
import sys
import shutil
import zipfile
import tempfile
from pathlib import Path
from Core import Logger
from Core.Utils import download_file, ensure_directory

# DirectX 12 Agility SDK Configuration
DX12_AGILITY_VERSION = "1.618.5"
DX12_NUGET_URL = f"https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/{DX12_AGILITY_VERSION}"
DX12_INSTALL_PATH = "./Engine/ThirdParty/DirectX12"

def validate() -> bool:
    """Validate DirectX 12 Agility SDK installation."""
    Logger.subheader("DirectX 12 Agility SDK")
    
    install_path = Path(DX12_INSTALL_PATH)
    
    # Check if already installed
    if (install_path / "build" / "native" / "include" / "d3d12.h").exists():
        Logger.success(f"DirectX 12 Agility SDK ({DX12_AGILITY_VERSION}) found")
        return True
    
    Logger.warning("DirectX 12 Agility SDK not found")
    return _install()

def _install() -> bool:
    """Download and install DirectX 12 Agility SDK."""
    from Core.Utils import prompt_yes_no
    
    if not prompt_yes_no(f"Download DirectX 12 Agility SDK {DX12_AGILITY_VERSION}?"):
        return False
    
    Logger.info(f"Downloading DirectX 12 Agility SDK {DX12_AGILITY_VERSION}...")
    
    # Create temporary directory for download
    temp_dir = tempfile.mkdtemp()
    nupkg_path = os.path.join(temp_dir, "d3d12.nupkg")
    
    try:
        # Download the NuGet package
        if not download_file(DX12_NUGET_URL, nupkg_path):
            Logger.error("Failed to download DirectX 12 Agility SDK")
            return False
        
        Logger.info("Extracting DirectX 12 Agility SDK...")
        
        # NuGet packages are just ZIP files
        install_path = Path(DX12_INSTALL_PATH)
        ensure_directory(str(install_path))
        
        with zipfile.ZipFile(nupkg_path, 'r') as zip_ref:
            zip_ref.extractall(install_path)
        
        # Verify extraction
        if not (install_path / "build" / "native" / "include" / "d3d12.h").exists():
            Logger.error("DirectX 12 Agility SDK extraction failed - d3d12.h not found")
            return False
        
        Logger.success(f"DirectX 12 Agility SDK {DX12_AGILITY_VERSION} installed")
        
        # Print installation summary
        Logger.info("")
        Logger.info("Installation Details:")
        Logger.info(f"  Location: {DX12_INSTALL_PATH}")
        Logger.info(f"  Headers: {DX12_INSTALL_PATH}/build/native/include/")
        Logger.info(f"  Libraries: {DX12_INSTALL_PATH}/build/native/bin/")
        Logger.info("")
        Logger.info("Available architectures:")
        bin_path = install_path / "build" / "native" / "bin"
        if bin_path.exists():
            for arch_dir in bin_path.iterdir():
                if arch_dir.is_dir():
                    dll_count = len(list(arch_dir.glob("*.dll")))
                    Logger.info(f"  - {arch_dir.name} ({dll_count} DLLs)")
        
        return True
        
    except Exception as e:
        Logger.error(f"Failed to install DirectX 12 Agility SDK: {e}")
        return False
    finally:
        # Cleanup temporary directory
        try:
            shutil.rmtree(temp_dir)
        except:
            pass

def get_include_path() -> str:
    """Get the include directory path for DirectX 12."""
    return os.path.abspath(f"{DX12_INSTALL_PATH}/build/native/include")

def get_library_path(architecture: str = "x64") -> str:
    """Get the library directory path for DirectX 12."""
    return os.path.abspath(f"{DX12_INSTALL_PATH}/build/native/bin/{architecture}")

if __name__ == "__main__":
    # Standalone test
    from Core import Logger
    Logger.header("DirectX 12 Agility SDK Setup")
    validate()
