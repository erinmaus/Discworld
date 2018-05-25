// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/relationships/resourceType.hpp"

extern "C"
MAPP_EXPORT int luaopen_mapp_resourcetype(lua_State* L)
{
	sol::usertype<twoflower::ResourceType> T(
		sol::call_constructor, sol::constructors<twoflower::ResourceType()>(),
		"id", sol::property(&twoflower::ResourceType::get_id, &twoflower::ResourceType::set_id),
		"name", sol::property(&twoflower::ResourceType::get_name, &twoflower::ResourceType::set_name)
	);

	sol::stack::push(L, T);

	return 1;
}
