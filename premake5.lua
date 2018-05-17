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
			runtime "release"

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
			links { "libboost_regex" }
			runtime "release"

		defines { "BOOST_ALL_NO_LIB" }

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

	project "Glooper"
		language "C++"
		kind "SharedLib"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/glooper/debug"
			targetdir "bin"
		configuration "Release"
			objdir "obj/glooper/reklease"
			targetdir "bin"
		configuration {}
			links { "Twoflower" }
			links { "Mapp" }
			links { "libboost_regex" }
			runtime "release"

		location "glooper"
		defines { "GLOOPER_BUILDING_DLL" }

		includedirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "include"),
			"glooper/include",
			"mapp/include",
			"twoflower/include"
		}

		files {
			"glooper/source/**.cpp",
			"glooper/include/**.hpp"
		}

		libdirs {
			path.join(_OPTIONS["deps"] or _DEFAULTS["deps"], "lib")
		}

	project "Rincewind"
		language "C#"
		kind "WindowedApp"

		configuration "Debug"
			targetsuffix "_debug"
			objdir "obj/rincewind/debug"
			targetdir "bin"
			defines { "RINCEWIND_DEBUG" }
		configuration "Release"
			objdir "obj/rincewind/release"
			targetdir "bin"
			defines { "RINCEWIND_RELEASE" }
		configuration {}
			links { "System" }
			links { "System.Windows.Forms" }
			clr "Unsafe"

		namespace "Dormouse.Rincewind"

		location "rincewind"

		files {
			"rincewind/**.cs"
		}

	test "basic_item"