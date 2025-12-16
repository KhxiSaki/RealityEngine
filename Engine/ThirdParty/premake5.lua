project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("ImGui/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("ImGui/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ImGui/imconfig.h",
		"ImGui/imgui.h",
		"ImGui/imgui.cpp",
		"ImGui/imgui_draw.cpp",
		"ImGui/imgui_internal.h",
		"ImGui/imgui_widgets.cpp",
		"ImGui/imstb_rectpack.h",
		"ImGui/imstb_textedit.h",
		"ImGui/imstb_truetype.h",
		"ImGui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
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

project "GLM"
	kind "StaticLib"
	language "C++"

	targetdir ("glm-1.0.2/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("glm-1.0.2/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
	"glm-1.0.2/glm/**.hpp",
		"glm-1.0.2/glm/**.inl",
	}

	filter "system:windows"
		systemversion "latest"
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

project "spdlog"
	kind "StaticLib"
	language "C++"

	targetdir ("spdlog-1.16.0/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("spdlog-1.16.0/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
	"spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"
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

project "NVRHI"
	kind "StaticLib"
	language "C++"

	targetdir ("nvrhi/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("nvrhi/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
	"nvrhi/include/nvrhi",
"nvrhi/src"
	}

	filter "system:windows"
		systemversion "latest"
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