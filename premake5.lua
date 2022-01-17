workspace "Info-Moisil"
	architecture "x86"
	configurations { "Debug", "Release" }
	startproject "Ecotron"
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLEW"] = "%{wks.location}/Info-Moisil/Vendor/GLEW/include"
	IncludeDir["GLFW"] = "%{wks.location}/Info-Moisil/Vendor/GLFW/include"
	IncludeDir["stb_image"] = "%{wks.location}/Info-Moisil/Vendor/stb_image"
	IncludeDir["glm"] = "%{wks.location}/Info-Moisil/Vendor/glm"
	
	group "Dependencies"
	include "Info-Moisil/Vendor/GLEW"
	include "Info-Moisil/Vendor/GLFW"
	group ""

	include "Info-Moisil"
