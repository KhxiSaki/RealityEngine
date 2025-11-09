
import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements
from SetupDependencies import SetupDependencies

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()


from SetupPremake import PremakeConfiguration as PremakeRequirements
SetupDependencies.Validate() 
from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./') # Change from devtools/scripts directory to root

premakeInstalled = PremakeRequirements.Validate()
VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

if (premakeInstalled):
    if platform.system() == "Windows":
        print("\nRunning premake...")
        subprocess.call([os.path.abspath("GenerateVisualStudioFiles.bat"), "nopause"])

    print("\nSetup completed!")
else:
    print("RealityEngine requires Premake to generate project files.")

