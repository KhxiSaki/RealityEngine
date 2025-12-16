import os
import sys
import subprocess

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

def main():
    from Core import Logger
    from Modules import SetupPremake
    import BuildConfig as Config
    from pathlib import Path
    
    Logger.header("Generate Project Files")
    
    premake_exe = Path(Config.PREMAKE_DIR) / "premake5.exe"
    
    if not premake_exe.exists():
        Logger.error("Premake not found! Run Setup.bat first.")
        return 1
    
    Logger.info("Running Premake...")
    result = subprocess.run([str(premake_exe.absolute()), "vs2022"])
    
    if result.returncode == 0:
        Logger.success("Visual Studio solution generated!")
    else:
        Logger.error("Premake failed!")
    
    return result.returncode

if __name__ == "__main__":
    os.chdir(os.path.join(os.path.dirname(__file__), "../.."))
    sys.exit(main())