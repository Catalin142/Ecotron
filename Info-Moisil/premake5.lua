project "Ecotron"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


	includedirs
	{
		"%{wks.location}/Info-Moisil/Source",
		"%{wks.location}/Info-Moisil/Source/Engine",
		"%{wks.location}/Info-Moisil/Vendor",
	}

	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Vendor/stb_image/**.h",
		"Vendor/stb_image/**.cpp",
		"Vendor/glm/glm/**.hpp",
		"Vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLEW_STATIC",
		"AL_LIBTYPE_STATIC"
	}

	includedirs
	{
		"Vendor;",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"Vendor/stb_image",
		"Source;",
		"Vendor/glm",
	}

	links 
	{
		"GLFW",
		"GLEW",
		"opengl32.lib",
	}


	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG=1"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE=1"
		runtime "Release"
		optimize "on"