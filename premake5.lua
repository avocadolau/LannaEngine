workspace "Lanna"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lanna/vendor/GLFW/include"
IncludeDir["Glad"] = "Lanna/vendor/Glad/include"
IncludeDir["ImGui"] = "Lanna/vendor/imgui"
IncludeDir["Glew"] = "Lanna/vendor/Glew/include/GL"
IncludeDir["JSON"] = "Lanna/vendor/rapidjson"
IncludeDir["MathGeoLib"] = "Lanna/vendor/MathGeoLib"
IncludeDir["PCG"] = "Lanna/vendor/PCG/include"
IncludeDir["assimp"] = "Lanna/vendor/assimp/include"
IncludeDir["glm"] = "Lanna/vendor/glm/glm"
IncludeDir["Optick"] = "Lanna/vendor/Optick/include"

include "Lanna/vendor/GLFW"
include "Lanna/vendor/Glad"
include "Lanna/vendor/imgui"
include "Lanna/vendor/Glew"
include "Lanna/vendor/Optick"

project "Lanna"
    location "Lanna"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lnpch.h"
	pchsource "Lanna/src/lnpch.cpp"

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
        "%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/rapidjson",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.MathGeoLib}",
        "%{IncludeDir.Glew}",
        "%{IncludeDir.PCG}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.Optick}"
	}

	links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
        "Glew",
		"opengl32.lib",
        "Optick"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

    filter "configurations:Debug"
        defines "LN_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"

    }

    includedirs
    {
        "Lanna/vendor/spdlog/include",
        "Lanna/vendor/rapidjson",
        "Lanna/vendor/imgui",
        "Lanna/src",
        "Lanna/vendor/glm/glm"
        "Lanna/vendor/Optik/include"
    }

    links
    {
        "Lanna"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        optimize "On"