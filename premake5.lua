workspace "RealityEngine"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "RealityEngine"

project "RealityEngine"
    kind "WindowedApp"
    language "C++"
    targetdir "Engine/Binaries/%{cfg.buildcfg}"
    objdir ("Engine/Intermediate/%{cfg.buildcfg}")
    files { 
        "Engine/Source/**.h", 
        "Engine/Source/**.cpp", 
        "Engine/Source/**.rc",
        "Engine/ThirdParty/imgui/*.h",
        "Engine/ThirdParty/imgui/*.cpp",
        "Engine/ThirdParty/imgui/backends/imgui_impl_win32.cpp", 
        "Engine/ThirdParty/imgui/backends/imgui_impl_dx12.cpp" 
    }

    includedirs { 
        "Engine/Source", 
        "Engine/ThirdParty/spdlog/include", 
        "Engine/ThirdParty/imgui", 
        "Engine/ThirdParty/imgui/backends" 
    }

    libdirs { 
        "$(DXSDK_DIR)Lib\\x64" 
    }

    links { 
        "d3d12", 
        "dxgi", 
        "d3dcompiler" 
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        cdialect "C17"
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"