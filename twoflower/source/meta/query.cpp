// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/meta/query.hpp"

twoflower::Query::Query(const RecordDefinition& definition) :
	definition(&definition)
{
	// Nothing.
}

bool twoflower::Query::get(const std::string& column, RecordValue& result) const
{
	if (definition->has_index(column))
	{
		return get(definition->get_index(column), result);
	}

	return false;
}

bool twoflower::Query::get(std::size_t index, RecordValue& result) const
{
	auto iter = values.find(index);
	if (iter != values.end())
	{
		result = iter->second;

		return true;
	}
	else
	{
		return false;
	}
}

bool twoflower::Query::set(const std::string& column, const RecordValue& value)
{
	if (definition->has_index(column))
	{
		return set(definition->get_index(column), value);
	}

	return false;
}

bool twoflower::Query::set(std::size_t index, const RecordValue& value)
{
	if (index < definition->count() &&
	    definition->get_type(index) == value.get_type())
	{
		values[index] = value;

		return true;
	}

	return false;
}

bool twoflower::Query::unset(const std::string& column)
{
	if (definition->has_index(column))
	{
		return unset(definition->get_index(column));
	}

	return false;
}

bool twoflower::Query::unset(std::size_t index)
{
	auto iter = values.find(index);
	if (iter != values.end())
	{
		values.erase(iter);

		return true;
	}

	return false;
}

bool twoflower::Query::empty() const
{
	return values.empty();
}

twoflower::Query::const_iterator twoflower::Query::begin() const
{
	return values.begin();
}

twoflower::Query::const_iterator twoflower::Query::end() const
{
	return values.end();
}
