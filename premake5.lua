workspace "BeerCatcher"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Spyen"
	location "Spyen"
	kind "StaticLib"
	language "C++"
	characterset "Unicode"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "spypch.h"
	pchsource "%{prj.name}/src/spypch.cpp"	

    flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }

	
	files {
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/vendor/glad/src/glad.c",
		"%{prj.name}/vendor/glm/include/glm/*.hpp",
		"%{prj.name}/vendor/glm/include/glm/*.inl",
		"%{prj.name}/vendor/entt/*.hpp",
		"%{prj.name}/vendor/miniaudio/include/miniaudio/*.h",
		"%{prj.name}/vendor/miniaudio/include/miniaudio/*.c",
		"%{prj.name}/vendor/stb_image/include/stb_image/*.h",
		"%{prj.name}/vendor/stb_image/include/stb_image/*.c"
	}
	
	
	includedirs {
		"Spyen/include",
		"Spyen/src",
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/glm/include",
		"%{prj.name}/vendor/glfw/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/entt",
		"%{prj.name}/vendor/stb_image/include",
		"%{prj.name}/vendor/miniaudio/include"
	}

	libdirs{
		"%{prj.name}/vendor/glfw/lib"
	}
	
	links {
		"glfw3",
		"opengl32"
	}

	filter "files:Spyen/vendor/**.c"
	flags {"NoPCH"}
	
	filter "system:windows"
		cppdialect "C++23"
		staticruntime "Off"
		systemversion "latest"
		
		
		defines {
			"SP_PLATFORM_WINDOWS",
			"SP_GL",
			"SPYEN_DLL_BUILD"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/BeerCatcher")
		}
		
	filter "configurations:Debug"
		defines "SP_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		runtime "Release"
		optimize "On"

project "BeerCatcher"
	location "BeerCatcher"
	kind "ConsoleApp"
	language "C++"
	characterset "Unicode"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	flags { "MultiProcessorCompile" }
    buildoptions { "/utf-8" }


	prebuildcommands{
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"Spyen/src",
		"Spyen/vendor/glad/include",
		"Spyen/vendor/glm/include",
		"Spyen/vendor/glfw/include",
		"Spyen/vendor/spdlog/include",
		"Spyen/vendor/entt",
		"Spyen/vendor/miniaudio/include"
	}

	libdirs{
	}
	
	links {
		"Spyen"
	}

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "Off"
		systemversion "latest"
		
		defines {
			"SP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		runtime "Debug"
		symbols "On"
		linkoptions { "/NODEFAULTLIB:MSVCRT" }
		
		
	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SP_DIST"
		runtime "Release"
		optimize "On"