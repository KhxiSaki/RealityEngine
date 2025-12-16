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
project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("glfw-3.4/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("glfw-3.4/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glfw-3.4/include/GLFW/glfw3.h",
		"glfw-3.4/include/GLFW/glfw3native.h",
		"glfw-3.4/src/glfw_config.h",
		"glfw-3.4/src/context.c",
		"glfw-3.4/src/init.c",
		"glfw-3.4/src/input.c",
		"glfw-3.4/src/monitor.c",
		"glfw-3.4/src/vulkan.c",
		"glfw-3.4/src/window.c"
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw-3.4/src/x11_init.c",
			"glfw-3.4/src/x11_monitor.c",
			"glfw-3.4/src/x11_window.c",
			"glfw-3.4/src/xkb_unicode.c",
			"glfw-3.4/src/posix_time.c",
			"glfw-3.4/src/posix_thread.c",
			"glfw-3.4/src/glx_context.c",
			"glfw-3.4/src/egl_context.c",
			"glfw-3.4/src/osmesa_context.c",
			"glfw-3.4/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw-3.4/src/win32_init.c",
			"glfw-3.4/src/win32_joystick.c",
			"glfw-3.4/src/win32_monitor.c",
			"glfw-3.4/src/win32_time.c",
			"glfw-3.4/src/win32_thread.c",
			"glfw-3.4/src/win32_window.c",
			"glfw-3.4/src/wgl_context.c",
			"glfw-3.4/src/egl_context.c",
			"glfw-3.4/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"