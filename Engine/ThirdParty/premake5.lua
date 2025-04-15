project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("ImGui/Binaries/" .. outputdir .. "/")
	objdir ("ImGui/Intermediate/" .. outputdir .. "/")

files
    {
        "ImGui/imconfig.h",
        "ImGui/imgui.h",
        "ImGui/imgui.cpp",
        "ImGui/imgui_draw.cpp",
        "ImGui/imgui_tables.cpp",
        "ImGui/imgui_widgets.cpp",
        "ImGui/imgui_internal.h",
        "ImGui/imstb_rectpack.h",
        "ImGui/imstb_textedit.h",
        "ImGui/imstb_truetype.h",
        "ImGui/imgui_demo.cpp",
        "ImGui/backends/imgui_impl_win32.*",
        "ImGui/backends/imgui_impl_vulkan.*"
    }


    includedirs
    {
        "ImGui",  -- Point to ImGui directory
        "%{IncludeDir.VulkanSDK}"
    }
	
	filter "system:windows"
		systemversion "latest"
		defines 
        {
            "_CRT_SECURE_NO_WARNINGS"
        }
		cppdialect "C++23"
		staticruntime "On"


	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++23"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"