workspace "PreViewer"
	startproject "Client"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "System"
		location "System"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
    systemversion "latest"  

    targetdir ("Bin/"..outputDir.."/%{prj.name}")
    objdir ("Bin-int/"..outputDir.."/%{prj.name}")

    pchheader "pch.h"
    pchsource "System/Source/pch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

	includedirs
    {
        "System/Source",
		"Vendor/spdlog/include",
    }

    filter "system:Windows"
    defines
    {
        "PV_PLATFORM_WINDOWS",
        "PV_RUNTIME_STATIC",
		"PV_ENABLE_ASSERTS",
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} \"../Bin/" .. outputDir .."/Client/\"" )
    }

    filter "configurations:Debug"
        defines "PV_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PV_RELEASE"
        runtime "Release"
        optimize "On"


project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    targetdir ("Bin/"..outputDir.."/%{prj.name}")
    objdir ("Bin-int/"..outputDir.."/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "System/Source",
		"Vendor/spdlog/include",
    }

    links
    {
        "System"
    }
    
    defines
    {
        "PV_PLATFORM_WINDOWS",
		"PV_ENABLE_ASSERTS",
    }

    filter "configurations:Debug"
        defines "PV_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PV_RELEASE"
        runtime "Release"
        optimize "On"