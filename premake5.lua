_DEFAULTS = {
	["deps"] = "."
}

newoption {
	trigger     = "deps",
	value       = "DIR",
	description = "Root directory containing dependencies."
}

function test(name)
	project(string.format("%s_%s", "test", name))
		language "C++"
		kind "ConsoleApp"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/twoflower/debug"
			targetdir "bin"
		configuration "Release"
			objdir "obj/twoflower/release"
			targetdir "bin"
		configuration {}
			links { "Mapp" }
			links { "Twoflower" }

		location(path.join("test", name))

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"mapp/include",
			"twoflower/include"
		}

		local root_path = path.join("test", name)

		files {
			path.join(path.join(root_path, "source"), "*.cpp"),
			path.join(path.join(root_path, "include"), "*.hpp")
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}
end

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

	test "basic_item"