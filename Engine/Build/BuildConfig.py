from dataclasses import dataclass, field
from typing import Optional
import platform

# ---- Version Requirements ----
PYTHON_VERSION_MIN = (3, 14)
PYTHON_PACKAGES = ["requests"]

# ---- Paths ----
PREMAKE_DIR = "./Engine/Binaries/Premake"
THIRD_PARTY_DIR = "./Engine/ThirdParty"
VULKAN_SDK_DIR = "./Engine/ThirdParty/SDK/VulkanSDK"

# ---- Premake Configuration ----
PREMAKE_VERSION = "5.0.0-beta7"
PREMAKE_DOWNLOAD_URL = f"https://github.com/premake/premake-core/releases/download/v{PREMAKE_VERSION}/premake-{PREMAKE_VERSION}-windows.zip"
PREMAKE_LICENSE_URL = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"

# ---- Vulkan Configuration ----
VULKAN_VERSION_REQUIRED = "1.4."
VULKAN_VERSION_INSTALL = "1.4.335.0"
VULKAN_DOWNLOAD_URL = f"https://sdk.lunarg.com/sdk/download/{VULKAN_VERSION_INSTALL}/windows/VulkanSDK-{VULKAN_VERSION_INSTALL}-Installer.exe"

@dataclass
class Dependency:
    name: str
    version: str
    url: str
    install_path: str
    extracted_folder: Optional[str] = None

# ---- Third Party Dependencies ----
DEPENDENCIES: list[Dependency] = [
    Dependency(
        name="ImGui",
        version="1.92.5",
        url="https://github.com/ocornut/imgui/archive/refs/tags/v1.92.5.zip",
        install_path=f"{THIRD_PARTY_DIR}/ImGui",
        extracted_folder="imgui-1.92.5"
    ), 
    Dependency(
        name="GLM",
        version="1.0.2",
        url="https://github.com/g-truc/glm/archive/refs/tags/1.0.2.zip",
        install_path=f"{THIRD_PARTY_DIR}/GLM",
        extracted_folder="GLM"
    ),
  Dependency(
        name="spdlog",
        version="1.16.0",
        url="https://github.com/gabime/spdlog/archive/refs/tags/v1.16.0.zip",
        install_path=f"{THIRD_PARTY_DIR}/spdlog",
        extracted_folder="spdlog"
    )
]