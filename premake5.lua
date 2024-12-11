workspace "RealityEngine"
architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RealityEngine"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "RealityEngine"
	location "Engine"
	kind "WindowedApp"
	language "C++"
	targetdir ("Engine/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Engine/Intermediate/" .. outputdir .. "/%{prj.name}")
	files
	{
		"Engine/Source/**.h",
		"Engine/Source/**.cpp",
		 "Engine/ThirdParty/imgui/imconfig.h",
		 "Engine/ThirdParty/imgui/imgui.h",
		 "Engine/ThirdParty/imgui/imgui.cpp",
		 "Engine/ThirdParty/imgui/imgui_draw.cpp",
		 "Engine/ThirdParty/imgui/imgui_internal.h",
		 "Engine/ThirdParty/imgui/imgui_widgets.cpp",
		 "Engine/ThirdParty/imgui/imstb_rectpack.h",
		 "Engine/ThirdParty/imgui/imstb_textedit.h",
		 "Engine/ThirdParty/imgui/imstb_truetype.h",
		 "Engine/ThirdParty/imgui/imgui_demo.cpp",
		 "Engine/ThirdParty/imgui/imgui_tables.cpp",
		        "Engine/ThirdParty/imgui/backends/imgui_impl_dx12.h",
		        "Engine/ThirdParty/imgui/backends/imgui_impl_dx12.cpp",
		        "Engine/ThirdParty/imgui/backends/imgui_impl_win32.h",
		        "Engine/ThirdParty/imgui/backends/imgui_impl_win32.cpp",
				"Engine/ThirdParty/flecs/include/flecs.h"
	}
	
	includedirs
	{
		"Engine/ThirdParty/imgui",
		"Engine/ThirdParty/imgui/backends",
		"Engine/ThirdParty/flecs/include"
	}

	links 
	{ 
		"d3dcompiler.lib",
		"dxgi.lib",
		"d3d12.lib"
	}


	filter "system:windows"
		cppdialect "C++latest"
        cdialect "C17"
		staticruntime "On"
		systemversion "latest"
	
