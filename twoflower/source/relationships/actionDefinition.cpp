// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/relationships/actionDefinition.hpp"

twoflower::ActionDefinition::ActionDefinition(const ID& id, const std::string& name) :
	id(id), name(name)
{
	// Nothing.
}

const twoflower::ID& twoflower::ActionDefinition::get_id() const
{
	return id;
}

void twoflower::ActionDefinition::set_id(const ID& value)
{
	id = value;
}

const std::string& twoflower::ActionDefinition::get_name() const
{
	return name;
}

void twoflower::ActionDefinition::set_name(const std::string& value)
{
	name = value;
}
