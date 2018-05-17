_DEFAULTS = {
	["deps"] = "."
}

newoption {
	trigger     = "deps",
	value       = "DIR",
	description = "Root directory containing dependencies."
}

solution "Discworld"
	configurations { "Debug", "Release" }
	platforms { "x64" }

	configuration "Debug"
		defines { "DEBUG" }
		symbols "On"

	configuration "Release"
		defines { "NDEBUG" }
		optimize "On"

	project "Twoflower"
		language "C++"
		kind "StaticLib"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/twoflower/debug"
			targetdir "bin"
		configuration "Release"
			objdir "obj/twoflower/release"
			targetdir "bin"
		configuration {}
			runtime "release"

		location "twoflower"

		files {
			"twoflower/source/**.cpp",
			"twoflower/source/**.c",
			"twoflower/include/**.hpp"
		}

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"twoflower/include"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}
