// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include "twoflower/brochure.hpp"
#include "detail/statement.hpp"
#include "detail/table.hpp"

twoflower::Brochure::ActionDefinitionIterator::ActionDefinitionIterator(
	const Brochure& brochure, Statement& statement) :
		brochure(&brochure),
		statement(new Statement(statement)),
		end(false)
{
	next();
}

twoflower::Brochure::ActionDefinitionIterator::~ActionDefinitionIterator()
{
	// Nothing.
}

twoflower::Brochure::ActionDefinitionIterator&
twoflower::Brochure::ActionDefinitionIterator::operator ++()
{
	next();
	return *this;
}

twoflower::Brochure::ActionDefinitionIterator
twoflower::Brochure::ActionDefinitionIterator::operator ++(int)
{
	next();
	return *this;
}

bool twoflower::Brochure::ActionDefinitionIterator::operator ==(
	const ActionDefinitionIterator& other) const
{
	return statement.get() == other.statement.get() || (end && other.end);
}

bool twoflower::Brochure::ActionDefinitionIterator::operator !=(
	const ActionDefinitionIterator& other) const
{
	return !(*this == other);
}

twoflower::Brochure::ActionDefinitionIterator::pointer
twoflower::Brochure::ActionDefinitionIterator::operator ->() const
{
	return &value;
}

twoflower::Brochure::ActionDefinitionIterator::value_type
twoflower::Brochure::ActionDefinitionIterator::operator *() const
{
	return value;
}

void twoflower::Brochure::ActionDefinitionIterator::next()
{
	if (end)
	{
		return;
	}

	if (!statement->next())
	{
		end = true;
	}
	else
	{
		int id;
		statement->get("id", id);

		std::string name;
		statement->get("name", name);

		value.set_id(id);
		value.set_name(name);
	}
}
