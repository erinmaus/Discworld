

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
			links { "sqlite3" }

		location "twoflower"

		files {
			"twoflower/source/**.cpp",
			"twoflower/include/**.hpp"
		}

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"twoflower/include"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}

	project "Mapp"
		language "C++"
		kind "StaticLib"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/mapp/debug"
			targetdir "bin"
		configuration "Release"
			objdir "obj/mapp/reklease"
			targetdir "bin"
		configuration {}
			links { "sqlite3" }
			links { "Twoflower" }

		location "mapp"

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"mapp/include",
			"twoflower/include"
		}

		files {
			"mapp/source/**.cpp",
			"mapp/include/**.hpp"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}
