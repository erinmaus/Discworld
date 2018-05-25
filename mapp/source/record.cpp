// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/meta/record.hpp"

static int mapp_record_get(lua_State* L)
{
	auto& record = sol::stack::get<twoflower::Record>(L, 1);

	twoflower::RecordValue value;
	bool success = false;
	if (lua_type(L, 2) == LUA_TSTRING)
	{
		auto field = luaL_checkstring(L, 2);
		success = record.get(field, value);
	}
	else if (lua_type(L, 2) == LUA_TNUMBER)
	{
		auto field = luaL_checkint(L, 2);
		if (field < 0)
		{
			luaL_error(L, "column must be greater than or equal to zero");
		}

		success = record.get((std::size_t)field, value);
	}
	else
	{
		luaL_error(
			L,
			"column must be string or integer; got %s",
			luaL_typename(L, 2));
	}
	
	if (success)
	{
		mapp_record_value_to_lua(L, value);
	}
	else
	{
		lua_pushnil(L);
	}

	return 1;
}

static int mapp_record_set(lua_State* L)
{
	auto& record = sol::stack::get<twoflower::Record>(L, 1);

	twoflower::RecordValue value;
	if (mapp_record_value_from_lua(L, value, 3))
	{
		if (lua_type(L, 2) == LUA_TSTRING)
		{
			auto field = luaL_checkstring(L, 2);
			record.set(field, value);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER)
		{
			auto field = luaL_checkint(L, 2);
			if (field < 0)
			{
				luaL_error(L, "column must be greater than or equal to zero");
			}

			record.set((std::size_t)field, value);
		}
		else
		{
			luaL_error(
				L,
				"column must be string or integer; got %s",
				luaL_typename(L, 2));
		}
	}

	return 0;
}

extern "C"
MAPP_EXPORT int luaopen_mapp_record(lua_State* L)
{
	sol::usertype<twoflower::Record> T(
		sol::call_constructor, sol::constructors<twoflower::Record(const twoflower::RecordDefinition&)>(),
		"get", &mapp_record_get,
		"set", &mapp_record_set
	);

	sol::stack::push(L, T);

	return 1;
}
