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
"%{IncludeDir.ImGui}/backends/imgui_impl_glfw.h",
		"%{IncludeDir.ImGui}/backends/imgui_impl_glfw.cpp",
		"%{IncludeDir.ImGui}/backends/imgui_impl_vulkan.h",
		"%{IncludeDir.ImGui}/backends/imgui_impl_vulkan.cpp"
	}
	
	includedirs
	{
		"Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.spdlog}/include"
	}
	
	links
	{
		"ImGui",
		"GLFW",
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