import os
from pathlib import Path
import Utils

class SetupDependencies:
    dependencies = [
        {
            "name": "ImGui",
            "version": "1.91.9b",
            "url": "https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.zip",
            "install_path": "./Engine/ThirdParty/ImGui",
            "extracted_folder": "imgui-1.91.9b"  # Folder inside the zip
        },
        # Add more dependencies as needed
    ]

    @classmethod
    def Validate(cls):
        for dep in cls.dependencies:
            install_dir = Path(dep["install_path"])
            if not install_dir.exists():
                print(f"{dep['name']} not found. Installing...")
                cls.InstallDependency(dep)
            else:
                print(f"{dep['name']} is already installed at {install_dir}")

    @classmethod
    def InstallDependency(cls, dep):
        zip_path = os.path.abspath(f"{dep['install_path']}.zip")
        install_path = os.path.abspath(dep["install_path"])
        
        # Download the zip file
        print(f"Downloading {dep['name']} from {dep['url']}")
        Utils.DownloadFile(dep["url"], zip_path)
        
        # Extract the zip file
        print(f"Extracting {zip_path} to {install_path}")
        Utils.UnzipFile(zip_path, deleteZipFile=True)
        
        # Move files from extracted folder to install path
        if "extracted_folder" in dep:
            extracted_dir = os.path.join(os.path.dirname(zip_path), dep["extracted_folder"])
            os.rename(extracted_dir, install_path)
        
        print(f"{dep['name']} installed successfully at {install_path}")

if __name__ == "__main__":
    SetupDependencies.Validate()