workspace "RealityEngine"
	architecture "x86_64"
	startproject "RealityEngine"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

group "Engine"
include "Engine"
group ""

group "Games"
include "EOC"
group ""

group "ThirdParty"
include "Engine/ThirdParty"
group ""