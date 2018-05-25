// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/relationships/actionConstraint.hpp"

int mapp_action_constraint_get_type(
	const twoflower::ActionConstraint& constraint)
{
	return (int)constraint.get_type();
}

void mapp_action_constraint_set_type(
	twoflower::ActionConstraint& constraint,
	int type)
{
	constraint.set_type((twoflower::ActionConstraint::Type)type);
}

extern "C"
MAPP_EXPORT int luaopen_mapp_actionconstraint(lua_State* L)
{
	sol::usertype<twoflower::ActionConstraint> T(
		sol::call_constructor, sol::constructors<twoflower::ActionConstraint()>(),
		"id", sol::property(&twoflower::ActionConstraint::get_id, &twoflower::ActionConstraint::set_id),
		"type", sol::property(&mapp_action_constraint_get_type, &mapp_action_constraint_set_type),
		"count", sol::property(&twoflower::ActionConstraint::get_count, &twoflower::ActionConstraint::set_count)
	);

	sol::stack::push(L, T);

	return 1;
}
