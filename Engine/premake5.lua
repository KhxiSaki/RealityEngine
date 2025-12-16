project "RealityEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	staticruntime "off"

	targetdir ("Binaries/" .. outputdir .. "/")
	objdir ("Intermediate/" .. outputdir .. "/")

files
	{
		"Source/**.h",
		"Source/**.cpp",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.GLM}",
"%{IncludeDir.NVRHI}"
	}
	
includedirs
{
    "Source",
    -- Use forward slashes for better compatibility
    "%{wks.location}/Engine/ThirdParty/ImGui",
    "%{wks.location}/Engine/ThirdParty/ImGui/backends",
    "%{IncludeDir.VulkanSDK}",
	"%{IncludeDir.GLM}",
	"%{IncludeDir.spdlog}",
"%{IncludeDir.spdlog}/include",
"%{IncludeDir.NVRHI}/include/nvrhi"
}

	
	links
	{
		"ImGui",
        "vulkan-1"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		
		}
		
		 -- Add Vulkan library directory
    filter {"system:windows", "configurations:*"}
        libdirs 
        {
            "%{VulkanSDK.LibraryDir}"
        }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
