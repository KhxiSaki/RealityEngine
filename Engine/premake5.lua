project "RealityEngine"
	kind "StaticLib"
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
		"Source"
	}
	
	links
	{
	
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
