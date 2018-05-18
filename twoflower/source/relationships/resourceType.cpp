// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/relationships/resourceType.hpp"

twoflower::ResourceType::ResourceType(const ID& id, const std::string& name) :
	id(id), name(name)
{
	// Nothing.
}

const twoflower::ID& twoflower::ResourceType::get_id() const
{
	return id;
}

void twoflower::ResourceType::set_id(const ID& value)
{
	id = value;
}

const std::string& twoflower::ResourceType::get_name() const
{
	return name;
}

void twoflower::ResourceType::set_name(const std::string& value)
{
	name = value;
}
