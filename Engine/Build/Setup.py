import os
import sys
import subprocess

# Add Build directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

def main():
    from Core import Logger
    
    Logger.header("RealityEngine Setup")
    
    # Step 1: Python
    from Modules import SetupPython
    if not SetupPython.validate():
        Logger.error("Python setup failed!")
        return 1
    
    # Step 2: Dependencies (downloads ImGui, etc.)
    from Modules import SetupDependencies
    SetupDependencies.validate()
    
    # Step 3: Premake
    from Modules import SetupPremake
    premake_ok = SetupPremake.validate()
    
    # Step 4: Vulkan
    from Modules import SetupVulkan
    SetupVulkan.validate()
    
    # Step 5: Git Submodules
    Logger.subheader("Git Submodules")
    Logger.info("Updating submodules...")
    result = subprocess.run(
        ["git", "submodule", "update", "--init", "--recursive"],
        capture_output=True, text=True
    )
    if result.returncode == 0:
        Logger.success("Submodules updated")
    else:
        Logger.warning("Failed to update submodules (is this a git repo?)")
    
    # Step 6: Compile Shaders
    from Modules import SetupShaders
    SetupShaders.validate()
    
    # Step 7: Generate project files
    if premake_ok:
        Logger.subheader("Project Generation")
        Logger.info("Generating Visual Studio solution...")
        premake_exe = SetupPremake.get_executable()
        subprocess.run([premake_exe, "vs2022"])
        Logger.success("Project files generated!")
    
    Logger.header("Setup Complete!")
    return 0

if __name__ == "__main__":
    os.chdir(os.path.join(os.path.dirname(__file__), "../.."))
    sys.exit(main())