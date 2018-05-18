// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/relationships/Resource.hpp"

twoflower::Resource::Resource(
	const ID& id,
	const std::string& name,
	const ResourceType& resource_type,
	bool is_singleton) :
		id(id),
		name(name),
		resource_type(resource_type),
		is_singleton(is_singleton)
{
	// Nothing.
}

const twoflower::ID& twoflower::Resource::get_id() const
{
	return id;
}

void twoflower::Resource::set_id(const ID& value)
{
	id = value;
}

const std::string& twoflower::Resource::get_name() const
{
	return name;
}

void twoflower::Resource::set_name(const std::string& value)
{
	name = value;
}

bool twoflower::Resource::get_is_singleton() const
{
	return is_singleton;
}

void twoflower::Resource::set_is_singleton(bool value)
{
	is_singleton = value;
}
