// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/relationships/actionDefinition.hpp"

extern "C"
MAPP_EXPORT int luaopen_mapp_actiondefinition(lua_State* L)
{
	sol::usertype<twoflower::ActionDefinition> T(
		sol::call_constructor, sol::constructors<twoflower::ActionDefinition()>(),
		"id", sol::property(&twoflower::ActionDefinition::get_id, &twoflower::ActionDefinition::set_id),
		"name", sol::property(&twoflower::ActionDefinition::get_name, &twoflower::ActionDefinition::set_name)
	);

	sol::stack::push(L, T);

	return 1;
}
