// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/relationships/action.hpp"

extern "C"
MAPP_EXPORT int luaopen_mapp_action(lua_State* L)
{
	sol::usertype<twoflower::Action> T(
		sol::call_constructor, sol::constructors<twoflower::Action()>(),
		"id", sol::property(&twoflower::Action::get_id, &twoflower::Action::set_id)
	);

	sol::stack::push(L, T);

	return 1;
}
