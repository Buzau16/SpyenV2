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

    flags { "MultiProcessorCompile" }

	
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


	filter "files:Spyen/vendor/**.c"
	flags {"NoPCH"}
	
    filter "action:gmake*"
        buildoptions { 
            "-std=c++23"
        }

    filter "system:linux"
		libdirs{
		    "%{prj.name}/vendor/glfw/lib/linux"
	    }
        links {
            "GL",
            "X11",
            "pthread",
            "dl",
            "glfw3"
        }
        buildoptions {
            "-finput-charset=UTF-8",
            "-fexec-charset=UTF-8"
        }
	filter "system:windows"
		cppdialect "C++23"
		staticruntime "Off"
		systemversion "latest"

        libdirs{
		    "%{prj.name}/vendor/glfw/lib/windows"
	    }
	

        links {
            "glfw3",
            "opengl32"
        }

		
        buildoptions { "/utf-8" }
		
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
	kind "WindowedApp"
	language "C++"
	characterset "Unicode"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	flags { "MultiProcessorCompile" }


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

	

    filter "action:gmake*"
        buildoptions { "-std=c++23" }

    filter "system:linux"

	libdirs{
		"Spyen/vendor/glfw/lib/linux"
	}
	
	links {
    	"Spyen",
    	"GL",
    	"X11",
   		"pthread",
   		"dl",
    	"glfw3"
	}
    buildoptions {
        "-finput-charset=UTF-8",
        "-fexec-charset=UTF-8"
    }

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "Off"
		systemversion "latest"

        buildoptions { "/utf-8" }

		libdirs{
			"Spyen/vendor/glfw/lib/windows"
		}	
	
		links {
    		"Spyen",
    		"GL",
    		"X11",
   			"pthread",
   			"dl",
    		"glfw3"
		}
		
		defines {
			"SP_PLATFORM_WINDOWS"
		}

        linkoptions { "/NODEFAULTLIB:MSVCRT" }

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
