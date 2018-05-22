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

		cppdialect "C++17"

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
			"twoflower/include/**.hpp",
			"twoflower/source/**.hpp",
		}

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"twoflower/include"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}

	project "Twoflower.Test"
		language "C++"
		kind "ConsoleApp"

		cppdialect "C++17"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/twoflower_test/debug"
			targetdir "bin"
		configuration "Release"
			objdir "obj/twoflower_test/release"
			targetdir "bin"
		configuration {}
			runtime "release"

		location "twoflower/test"

		files {
			"twoflower/test/include/**.hpp",
			"twoflower/test/source/**.cpp"
		}

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"twoflower/include",
			"twoflower/test/include"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}

		links { "Twoflower" }
