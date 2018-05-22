// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/meta/recordValue.hpp"

void twoflower::RecordValue::set(int value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::integer;
}

void twoflower::RecordValue::set(float value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::real;
}

void twoflower::RecordValue::set(const std::string& value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::text;
}

void twoflower::RecordValue::set(const std::vector<std::uint8_t>& value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::blob;
}

void twoflower::RecordValue::set(const Action& value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::action;
}

void twoflower::RecordValue::set(const Resource& value)
{
	instance = InstanceType(value);
	type = RecordDefinition::Type::resource;
}

bool twoflower::RecordValue::get(int& result)
{
	auto r = std::get_if<int>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

bool twoflower::RecordValue::get(float& result)
{
	auto r = std::get_if<float>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

bool twoflower::RecordValue::get(std::string& result)
{
	auto r = std::get_if<std::string>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

bool twoflower::RecordValue::get(std::vector<std::uint8_t>& result)
{
	auto r = std::get_if<std::vector<std::uint8_t>>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

bool twoflower::RecordValue::get(Action& result)
{
	auto r = std::get_if<Action>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

bool twoflower::RecordValue::get(Resource& result)
{
	auto r = std::get_if<Resource>(&instance);
	if (r != nullptr)
	{
		result = *r;
		return true;
	}

	return false;
}

twoflower::RecordDefinition::Type twoflower::RecordValue::get_type() const
{
	return type;
}

void twoflower::RecordValue::make_default(RecordDefinition::Type type)
{
	switch (type)
	{
		case RecordDefinition::Type::integer:
			{
				int value = 0;
				set(value);
			}
			break;
		case RecordDefinition::Type::text:
			{
				std::string value;
				set(value);
			}
			break;
		case RecordDefinition::Type::real:
			{
				float value = 0.0f;
				set(value);
			}
			break;
		case RecordDefinition::Type::blob:
			{
				std::vector<std::uint8_t> value;
				set(value);
			}
			break;
		case RecordDefinition::Type::action:
			{
				Action value;
				set(value);
			}
			break;
		case RecordDefinition::Type::resource:
			{
				Resource value;
				set(value);
			}
			break;
		default:
			throw std::runtime_error("unknown type");
	}
}
