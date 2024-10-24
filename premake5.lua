workspace "RealityEngine"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "RealityEngine"

project "RealityEngine"
    kind "WindowedApp"
    language "C++"
    targetdir "Engine/Binaries/%{cfg.buildcfg}"

    files { "Engine/Source/**.h", "Engine/Source/**.cpp", "Engine/Source/**.rc" }

    includedirs { "Engine/Source", "Engine/ThirdParty/spdlog/include", "Engine/ThirdParty/imgui" }

    -- Link with DirectX 12 libraries
    links { "d3d12.lib", "dxgi.lib", "d3dcompiler.lib" }

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"