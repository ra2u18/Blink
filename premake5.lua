workspace "Blink"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Blink/vendor/GLFW/include"
IncludeDir["Glad"] = "Blink/vendor/Glad/include"
IncludeDir["ImGui"] = "Blink/vendor/imgui"
IncludeDir["glm"] = "Blink/vendor/glm"

-- Include GLFW premake file into this section of code
include "Blink/vendor/GLFW"
include "Blink/vendor/Glad"
include "Blink/vendor/imgui"

project "Blink"
	location "Blink"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "blpch.h"
	pchsource "Blink/src/blpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spgdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BL_PLATFORM_WINDOWS",
			"BL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "configurations:Debug"
		defines "BL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BL_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "BL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Blink/vendor/spgdlog/include",
		"Blink/src",
		"Blink/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Blink"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BL_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "BL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BL_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "BL_DIST"
		runtime "Release"
		optimize "on"