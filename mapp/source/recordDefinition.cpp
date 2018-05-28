// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/meta/recordDefinition.hpp"

static void mapp_record_definition_define(
	twoflower::RecordDefinition& definition,
	const std::string& column,
	int type)
{
	definition.define(column, (twoflower::RecordDefinition::Type)type);
}

static int mapp_record_definition_get_type(
	twoflower::RecordDefinition& definition,
	std::size_t index)
{
	return (int)definition.get_type(index);
}

static const std::string& mapp_record_definition_get_name(
	const twoflower::RecordDefinition& record)
{
	return record.get_name();
}

static std::string mapp_record_definition_get_column_name(
	const twoflower::RecordDefinition& record,
	std::size_t index)
{
	return record.get_name(index);
}

extern "C"
MAPP_EXPORT int luaopen_mapp_recorddefinition(lua_State* L)
{
	sol::usertype<twoflower::RecordDefinition> T(
		sol::call_constructor, sol::constructors<twoflower::RecordDefinition(const std::string&)>(),
		"name", sol::property(&mapp_record_definition_get_name),
		"define", &mapp_record_definition_define,
		"count", sol::property(&twoflower::RecordDefinition::count),
		"getName", &mapp_record_definition_get_column_name,
		"getType", &mapp_record_definition_get_type,
		"getIndex", &twoflower::RecordDefinition::get_index,
		"hasIndex", &twoflower::RecordDefinition::has_index);

	sol::stack::push(L, T);

	return 1;
}
