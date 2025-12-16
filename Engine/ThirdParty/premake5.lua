project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("imgui-docking/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("imgui-docking/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imgui-docking/imconfig.h",
		"imgui-docking/imgui.h",
		"imgui-docking/imgui.cpp",
		"imgui-docking/imgui_draw.cpp",
		"imgui-docking/imgui_internal.h",
		"imgui-docking/imgui_widgets.cpp",
		"imgui-docking/imstb_rectpack.h",
		"imgui-docking/imstb_textedit.h",
		"imgui-docking/imstb_truetype.h",
		"imgui-docking/imgui_demo.cpp",
		"imgui-docking/imgui_tables.cpp"
	}

	includedirs
	{
		"imgui-docking",
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.VulkanSDK}"
	}

	defines
	{
		"IMGUI_IMPL_VULKAN_USE_VOLK=0"
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
		"glfw-3.4/src/platform.c",
		"glfw-3.4/src/vulkan.c",
		"glfw-3.4/src/window.c",
		"glfw-3.4/src/egl_context.c",
		"glfw-3.4/src/osmesa_context.c",
		"glfw-3.4/src/null_platform.h",
		"glfw-3.4/src/null_joystick.h",
		"glfw-3.4/src/null_init.c",
		"glfw-3.4/src/null_monitor.c",
		"glfw-3.4/src/null_window.c",
		"glfw-3.4/src/null_joystick.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw-3.4/src/win32_module.c",
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
			"glfw-3.4/src/posix_module.c",
			"glfw-3.4/src/posix_time.c",
			"glfw-3.4/src/posix_thread.c",
			"glfw-3.4/src/posix_poll.c",
			"glfw-3.4/src/glx_context.c",
			"glfw-3.4/src/egl_context.c",
			"glfw-3.4/src/osmesa_context.c",
			"glfw-3.4/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

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
		"glm-1.0.2/glm/**.inl"
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
		"spdlog-1.16.0/include/**.h"
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