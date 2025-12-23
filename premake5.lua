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
IncludeDir["ImGui"] = "%{wks.location}/Engine/ThirdParty/imgui-docking"
IncludeDir["VulkanSDK"] = os.getenv("VULKAN_SDK") .. "/Include"
IncludeDir["GLFW"] = "%{wks.location}/Engine/ThirdParty/glfw-3.4"
IncludeDir["GLM"] = "%{wks.location}/Engine/ThirdParty/glm-1.0.2"
IncludeDir["spdlog"] = "%{wks.location}/Engine/ThirdParty/spdlog-1.16.0"
IncludeDir["DirectX12"] = "%{wks.location}/Engine/ThirdParty/DirectX12/build/native/include"

VulkanSDK = {}
VulkanSDK.LibraryDir = os.getenv("VULKAN_SDK") .. "/Lib"

DirectX12SDK = {}
DirectX12SDK.IncludeDir = "%{wks.location}/Engine/ThirdParty/DirectX12/build/native/include"
DirectX12SDK.BinDir = "%{wks.location}/Engine/ThirdParty/DirectX12/build/native/bin/x64"

-- Validate Vulkan SDK path
if not os.isdir(VulkanSDK.LibraryDir) then
    error("Vulkan SDK not found! Please install it and set VULKAN_SDK environment variable")
end

group "Engine"
include "Engine"
group ""

group "ThirdParty"
include "Engine/ThirdParty"
group ""