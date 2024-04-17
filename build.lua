workspace "Flarea"
    architecture "x64"
    configurations 
    {
        "Debug", 
        "Release"
    }
    startproject "Flarea"

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

IncludeDirs = { }
IncludeDirs["GLFW"] = "Flarea/External/glfw/include"
IncludeDirs["GLAD"] = "Flarea/External/GLAD/include"

include "Flarea/External/glfw"
include "Flarea/External/GLAD"

project "Flarea"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/External/Lua/*.c",
        "%{prj.name}/External/Lua/*.hpp",
        -- "%{prj.name}/External/rapidjson/*.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/External",
        "%{prj.name}/src",

        -- the followings are specific modules
        "%{prj.name}/External/spdlog/include",

        -- includes of sub-projects
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.GLAD}"
    }
    
    filter "system:Windows"
        location "Flarea"
        targetdir ("x64/%{cfg.buildcfg}")
        objdir ("x64/obj/%{cfg.buildcfg}")

        pchheader "flrpch.h"
        pchsource "%{prj.name}/src/flrpch.cpp"

        links 
        {
            "GLFW",
            "GLAD",
            "opengl32.lib"
        }
        
        libdirs 
        { 

        }
        
        -- postbuildcommands ("copy External\\dlls\\* ..\\x64\\%{cfg.buildcfg}")

        defines { "FLR_WINDOWS" }
        staticruntime "On"
        systemversion "latest"

    filter "files:**.c"
        flags {"NoPCH"}

    filter "configurations:Debug"
        defines { "FLR_DEBUG" }
        symbols "On"
        optimize "Speed"

    filter "configurations:Release"
        defines { "FLR_RELEASE" }
        defines { "NDEBUG" }
        symbols "On"
        optimize "Speed"