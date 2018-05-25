// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/relationships/resource.hpp"

extern "C"
MAPP_EXPORT int luaopen_mapp_resource(lua_State* L)
{
	sol::usertype<twoflower::Resource> T(
		sol::call_constructor, sol::constructors<twoflower::Resource()>(),
		"id", sol::property(&twoflower::Resource::get_id, &twoflower::Resource::set_id),
		"name", sol::property(&twoflower::Resource::get_name, &twoflower::Resource::set_name),
		"isSingleton", sol::property(&twoflower::Resource::get_is_singleton, &twoflower::Resource::set_is_singleton)
	);

	sol::stack::push(L, T);

	return 1;
}
