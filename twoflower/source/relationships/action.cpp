// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/relationships/action.hpp"

twoflower::Action::Action(
	const ID& id,
	const ActionDefinition& action_definition) :
		id(id), action_definition(action_definition)
{
	// Nothing.
}

const twoflower::ID& twoflower::Action::get_id() const
{
	return id;
}

void twoflower::Action::set_id(const ID& value)
{
	id = value;
}

const twoflower::ActionDefinition&
twoflower::Action::get_action_definition() const
{
	return action_definition;
}

void twoflower::Action::set_action_definition(const ActionDefinition& value)
{
	action_definition = value;
}
