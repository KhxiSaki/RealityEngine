workspace "RealityEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "EraOfChange"  -- Change this to your game project name

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Engine Project
project "RealityEngine"
    location "Engine"  -- This will create a filter in Visual Studio
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
        "Engine/ThirdParty/imgui/backends/imgui_impl_win32.cpp"
    }

    includedirs
    {
        "Engine/ThirdParty/imgui",
        "Engine/ThirdParty/imgui/backends"
    }

    links 
    { 
        "d3dcompiler.lib",
        "dxgi.lib",
        "d3d12.lib"
    }

    filter "system:windows"
        cppdialect "C++latest"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "Full"

-- Game Project
project "EraOfChange"  -- Change this to your actual game project name
    location "Games/EraOfChange"  -- This will create a filter in Visual Studio under Games
    kind "WindowedApp"  -- Change to "ConsoleApp" if you want a console application
    language "C++"
    targetdir ("Games/EraOfChange/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Games/EraOfChange/Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Games/EraOfChange/Source/**.h",
        "Games/EraOfChange/Source/**.cpp"
    }

    includedirs
    {
        "Engine/Source",
        "Engine/ThirdParty/imgui"
    }

    links
    {
        "RealityEngine"  -- Link to the engine project
    }

    filter "system:windows"
        cppdialect "C++latest"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "Full"