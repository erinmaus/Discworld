// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cassert>
#include <stdexcept>
#include "twoflower/id.hpp"

const twoflower::ID twoflower::ID::NIL = twoflower::ID(0);

twoflower::ID::ID()
{
	// Nothing.
}

twoflower::ID::ID(int value)
{
	if (value < 0)
	{
		throw std::runtime_error("id must be non-negative");
	}

	id = value;
}

twoflower::ID::ID(ID&& other)
{
	*this = other;
}

twoflower::ID::operator int() const
{
	return id;
}

bool twoflower::ID::operator <(const ID& other)
{
	return id < other.id;
}

bool twoflower::ID::operator >(const ID& other)
{
	return id > other.id;
}

bool twoflower::ID::operator <=(const ID& other)
{
	return id <= other.id;
}

bool twoflower::ID::operator >=(const ID& other)
{
	return id >= other.id;
}

bool twoflower::ID::operator ==(const ID& other)
{
	return id == other.id;
}

bool twoflower::ID::operator !=(const ID& other)
{
	return !(*this == other);
}

twoflower::ID& twoflower::ID::operator =(int value)
{
	if (value < 0)
	{
		throw std::runtime_error("id must be non-negative");
	}

	id = value;

	return *this;
}

twoflower::ID& twoflower::ID::operator =(ID&& other)
{
	assert(!(other.id < 0) && "other ID is negative");

	id = other.id;
	other.id = 0;

	return *this;
}
