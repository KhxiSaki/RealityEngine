workspace "RealityEngine"
	architecture "x86_64"
	startproject "RealityEngine"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "/Engine/ThirdParty/ImGui"
IncludeDir["VulkanSDK"] = os.getenv("VULKAN_SDK") .. "/Include"

VulkanSDK = {}
VulkanSDK.LibraryDir = os.getenv("VULKAN_SDK") .. "/Lib"

-- Validate Vulkan SDK path
if not os.isdir(VulkanSDK.LibraryDir) then
    error("Vulkan SDK not found! Please install it and set VULKAN_SDK environment variable")
end

group "Engine"
include "Engine"
group ""

group "ThirdParty"
--include "Engine/ThirdParty"
group ""