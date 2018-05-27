// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/meta/record.hpp"

twoflower::Record::Record(const RecordDefinition& definition) :
	definition(&definition)
{
	for (std::size_t i = 0; i < definition.count(); ++i)
	{
		RecordValue value;
		value.make_default(definition.get_type(i));

		values.push_back(value);
	}
}

bool twoflower::Record::get(const std::string& column, RecordValue& result) const
{
	if (definition->has_index(column))
	{
		return get(definition->get_index(column), result);
	}

	return false;
}

bool twoflower::Record::get(std::size_t index, RecordValue& result) const
{
	if (index < values.size())
	{
		result = values[index];

		return true;
	}
	else
	{
		return false;
	}
}

bool twoflower::Record::set(const std::string& column, const RecordValue& value)
{
	if (definition->has_index(column))
	{
		return set(definition->get_index(column), value);
	}

	return false;
}

bool twoflower::Record::set(std::size_t index, const RecordValue& value)
{
	if (index < values.size())
	{
		values[index] = value;

		return true;
	}
	else
	{
		return false;
	}
}
