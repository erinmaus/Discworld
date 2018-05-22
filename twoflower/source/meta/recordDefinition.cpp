// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <stdexcept>
#include "twoflower/meta/recordDefinition.hpp"

twoflower::RecordDefinition::RecordDefinition(const std::string& name) :
	name(name)
{
	define("id", Type::integer);
}

const std::string& twoflower::RecordDefinition::get_name() const
{
	return name;
}

void twoflower::RecordDefinition::define(const std::string& column, Type type)
{
	if (columns.find(column) != columns.end())
	{
		throw std::runtime_error("column already exists");
	}

	columns.emplace(column, count());
	entryDefinitions.emplace_back(column, type);
}

std::size_t twoflower::RecordDefinition::count() const
{
	return entryDefinitions.size();
}

std::string twoflower::RecordDefinition::get_name(std::size_t index) const
{
	return std::get<ENTRY_DEFINITION_COLUMN>(entryDefinitions.at(index));
}

twoflower::RecordDefinition::Type
twoflower::RecordDefinition::get_type(std::size_t index) const
{
	return std::get<ENTRY_DEFINITION_TYPE>(entryDefinitions.at(index));
}

std::size_t twoflower::RecordDefinition::get_index(
	const std::string& column) const
{
	auto iter = columns.find(column);
	if (iter == columns.end())
	{
		throw std::runtime_error("column not found");
	}

	return iter->second;
}
