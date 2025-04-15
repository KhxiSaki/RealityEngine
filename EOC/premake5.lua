project "EOC"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	staticruntime "off"

	targetdir ("Binaries/" .. outputdir .. "/")
	objdir ("Intermediate/" .. outputdir .. "/")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		
		"Engine/Source"
	}

	links
	{
		"RealityEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"