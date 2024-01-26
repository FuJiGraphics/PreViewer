workspace "PreViewer"
	startproject "System"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "System"
		location "System"
		kind "WindowedApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"
    systemversion "latest"  

    targetdir ("Build/Bin/"..outputDir.."/%{prj.name}")
    objdir ("Build/Bin-int/"..outputDir.."/%{prj.name}")

    pchheader "pch.h"
    pchsource "System/Source/pch.cpp"

	IncludeDir = {};
	IncludeDir["Pylon"] = "%{prj.name}/Vendor/Pylon"

    files
    {
		"%{prj.name}/Resource/*",
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

	includedirs
    {
        "%{prj.name}/Source",
		"Vendor/Pylon/include"
		
    }

	links
	{
		"GCBase_MD_VC141_v3_1_Basler_pylon.lib",
		"GenApi_MD_VC141_v3_1_Basler_pylon.lib",
		"PylonBase_v6_0.lib",
		"PylonC.lib",
		"PylonGUI_v6_0.lib",
		"PylonUtility_v6_0.lib"
	}

	libdirs 
	{ 
		"Vendor/Pylon/lib/x64" 
	}

    filter "system:Windows"
    defines
    {
        "PV_PLATFORM_WINDOWS",
    }

	flags 
	{ 
		"MFC" 
	}

    filter "configurations:Debug"
        defines "PV_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PV_RELEASE"
        runtime "Release"
        optimize "On"

