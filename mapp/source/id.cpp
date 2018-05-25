// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/id.hpp"

static int id_value(const twoflower::ID& id)
{
	return (int)id;
}

extern "C"
MAPP_EXPORT int luaopen_mapp_id(lua_State* L)
{
	sol::usertype<twoflower::ID> T(
		sol::call_constructor, sol::constructors<twoflower::ID(), twoflower::ID(int)>(),
		"value", sol::property(&id_value)
	);

	sol::stack::push(L, T);

	return 1;
}
