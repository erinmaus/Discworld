// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/meta/query.hpp"

static int mapp_query_get(lua_State* L)
{
	auto& query = sol::stack::get<twoflower::Query>(L, 1);

	twoflower::RecordValue value;
	bool success = false;
	if (lua_type(L, 2) == LUA_TSTRING)
	{
		auto field = luaL_checkstring(L, 2);
		success = query.get(field, value);
	}
	else if (lua_type(L, 2) == LUA_TNUMBER)
	{
		auto field = luaL_checkint(L, 2);
		if (field < 0)
		{
			luaL_error(L, "column must be greater than or equal to zero");
		}

		success = query.get((std::size_t)field, value);
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

static int mapp_query_set(lua_State* L)
{
	auto& query = sol::stack::get<twoflower::Query>(L, 1);

	twoflower::RecordValue value;
	if (mapp_record_value_from_lua(L, value, 3))
	{
		if (lua_type(L, 2) == LUA_TSTRING)
		{
			auto field = luaL_checkstring(L, 2);
			query.set(field, value);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER)
		{
			auto field = luaL_checkint(L, 2);
			if (field < 0)
			{
				luaL_error(L, "column must be greater than or equal to zero");
			}
			
			query.set((std::size_t)field, value);
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

static int mapp_query_unset(lua_State* L)
{
	auto& query = sol::stack::get<twoflower::Query>(L, 1);

	if (lua_type(L, 2) == LUA_TSTRING)
	{
		auto field = luaL_checkstring(L, 2);
		query.unset(field);
	}
	else if (lua_type(L, 2) == LUA_TNUMBER)
	{
		auto field = luaL_checkint(L, 2);
		if (field < 0)
		{
			luaL_error(L, "column must be greater than or equal to zero");
		}

		query.unset((std::size_t)field);
	}
	else
	{
		luaL_error(
			L,
			"column must be string or integer; got %s",
			luaL_typename(L, 2));
	}

	return 0;
}


extern "C"
MAPP_EXPORT int luaopen_mapp_query(lua_State* L)
{
	sol::usertype<twoflower::Query> T(
		sol::call_constructor, sol::constructors<twoflower::Query(const twoflower::RecordDefinition&)>(),
		"get", &mapp_query_get,
		"set", &mapp_query_set,
		"unset", &mapp_query_unset,
		"empty", sol::property(&twoflower::Query::empty)
	);

	sol::stack::push(L, T);

	return 1;
}
