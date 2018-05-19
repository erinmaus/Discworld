// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/relationships/actionConstraint.hpp"

twoflower::ActionConstraint::ActionConstraint(
	const ID& id,
	Type type,
	float count) :
		id(id),
		type(type),
		count(count)
{
	// Nothing.
}

const twoflower::ID& twoflower::ActionConstraint::get_id() const
{
	return id;
}

void twoflower::ActionConstraint::set_id(const ID& value)
{
	id = value;
}

twoflower::ActionConstraint::Type twoflower::ActionConstraint::get_type() const
{
	return type;
}

void twoflower::ActionConstraint::set_type(Type value)
{
	type = value;
}

float twoflower::ActionConstraint::get_count() const
{
	return count;
}

void twoflower::ActionConstraint::set_count(float value)
{
	count = value;
}
