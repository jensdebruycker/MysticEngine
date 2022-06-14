workspace "MysticEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MysticEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MysticEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MysticEngine/vendor/imgui"
IncludeDir["glm"] = "MysticEngine/vendor/glm"
IncludeDir["stb_image"] = "MysticEngine/vendor/stb_image"

include "MysticEngine/vendor/GLFW"
include "MysticEngine/vendor/Glad"
include "MysticEngine/vendor/imgui"

project "MysticEngine"
	location "MysticEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mspch.h"
	pchsource "MysticEngine/src/mspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MS_PLATFORM_WINDOWS",
			"MS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines
		{
			"MS_DEBUG",
			"MS_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MS_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MysticEngine/vendor/spdlog/include",
		"MysticEngine/vendor/Glad/include",
		"MysticEngine/vendor/glm",
		"MysticEngine/src",
		"MysticEngine/vendor"
	}

	links 
	{
		"MysticEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MS_DIST"
		runtime "Release"
		symbols "on"