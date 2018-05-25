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
#include "twoflower/relationships/resource.hpp"
#include "twoflower/meta/recordDefinition.hpp"

void mapp_record_value_to_lua(lua_State* L, const twoflower::RecordValue& value)
{
	switch (value.get_type())
	{
		case twoflower::RecordDefinition::Type::integer:
			{
				int v;
				if (value.get(v))
				{
					lua_pushnumber(L, v);
				}
			}
			break;
		case twoflower::RecordDefinition::Type::text:
			{
				std::string v;
				if (value.get(v))
				{
					lua_pushstring(L, v.c_str());
				}
			}
			break;
		case twoflower::RecordDefinition::Type::real:
			{
				float v;
				if (value.get(v))
				{
					lua_pushnumber(L, v);
				}
			}
		case twoflower::RecordDefinition::Type::blob:
			{
				luaL_error(L, "blob unsupported");
			}
			break;
		case twoflower::RecordDefinition::Type::action:
			{
				twoflower::Action v;
				if (value.get(v))
				{
					sol::stack::push(L, v);
				}
			}
			break;
		case twoflower::RecordDefinition::Type::resource:
			{
				twoflower::Resource v;
				if (value.get(v))
				{
					sol::stack::push(L, v);
				}
			}
			break;
	}
}

bool mapp_record_value_from_lua(
	lua_State* L,
	twoflower::RecordValue& result,
	int index)
{
	int type = lua_type(L, index);

	switch (type)
	{
		case LUA_TNUMBER:
			{
				float value = luaL_checknumber(L, index);
				result.set(value);
			}
			return true;
		case LUA_TSTRING:
			{
				const char* value = luaL_checkstring(L, index);
				result.set(value);
			}
			return true;
		case LUA_TBOOLEAN:
			{
				int value = lua_toboolean(L, index);
				result.set(value);
			}
			return true;
		case LUA_TUSERDATA:
			{
				if (sol::stack::check<twoflower::Action>(L, index))
				{
					auto& value = sol::stack::get<twoflower::Action>(L, index);
					result.set(value);
				}
				else if (sol::stack::check<twoflower::Resource>(L, index))
				{
					auto& value = sol::stack::get<twoflower::Resource>(L, index);
					result.set(value);
				}
			}
			return true;
	}

	return false;
}
