// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <stdexcept>
#include "twoflower/brochure.hpp"
#include "detail/database.hpp"
#include "detail/statement.hpp"

twoflower::Brochure::Actions::Actions(const Brochure& brochure) :
	brochure(&brochure),
	is_limited(false)
{
	// Nothing.
}

twoflower::Brochure::Actions::Actions(
	const Brochure& brochure, const Resource& resource) :
	brochure(&brochure),
	resource(resource),
	is_limited(true)
{
	// Nothing.
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::by_type(int type) const
{
	Action::Type t;
	t.id = type;

	return by_type(t);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::by_type(const Action::Type& type) const
{
	std::string query = "SELECT * FROM ActionInstance WHERE action_id=:action_id";
	if (is_limited)
	{
		query += " AND resource_id=:resource_id";
	}
	query += ";";

	auto statement = brochure->database->create_statement(query);
	statement.bind(":action_id", type.id);
	statement.bind(":resource_id", resource.get_id());
	return const_iterator(*brochure->database, statement);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::by_name(const std::string& type, const std::string& name) const
{
	return by_name(type + "." + name);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::by_name(const std::string& name) const
{
	std::string query = "SELECT * FROM ActionInstance"
		" INNER JOIN ActionDefinition"
		" ON ActionDefinition.name=:name";
	if (is_limited)
	{
		query += " WHERE resource_id=:resource_id";
	}
	query += ";";

	auto statement = brochure->database->create_statement(query);
	statement.bind(":name", name);
	statement.bind(":resource_id", resource.get_id());
	return const_iterator(*brochure->database, statement);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::getters() const
{
	std::string query = "SELECT * FROM ActionInstance";
	query += " INNER JOIN ActionDefinition"
		" ON ActionDefinition.id=ActionInstance.action_id"
		" AND ActionDefinition.getter=1";
	if (is_limited)
	{
		query += " WHERE resource_id=:id";
	}
	query += ";";

	auto statement = brochure->database->create_statement(query);
	statement.bind(":id", resource.get_id());
	return const_iterator(*brochure->database, statement);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::definitions() const
{
	auto statement = brochure->database->create_statement(
		"SELECT * FROM ActionDefinition;");
	return const_iterator(*brochure->database, statement, false);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::definitions(const std::string& name) const
{
	auto statement = brochure->database->create_statement(
		"SELECT * FROM ActionDefinition WHERE name=?");
	statement.bind(1, name);
	return const_iterator(*brochure->database, statement, false);
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::begin() const
{
	if (!is_limited)
	{
		auto statement = brochure->database->create_statement(
			"SELECT * FROM ActionInstance;");
		return const_iterator(*brochure->database, statement);
	}
	else
	{
		auto statement = brochure->database->create_statement(
			"SELECT * FROM ActionInstance"
			" WHERE resource_id=?;");
		statement.bind(1, resource.get_id());
		return const_iterator(*brochure->database, statement);
	}
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::end() const
{
	return const_iterator();
}

bool twoflower::Brochure::Actions::has(const Action& action) const
{
	if (action.get_id())
	{
		return has(action.get_id());
	}
	else
	{
		return brochure->has_action_definition(action.get_type().id);
	}
}

bool twoflower::Brochure::Actions::has(int id) const
{
	auto statement = brochure->database->create_statement(
		"SELECT * FROM ActionInstance WHERE id=?;");
	statement.bind(1, id);

	return statement.execute() == 1;
}

twoflower::Action twoflower::Brochure::Actions::get(int id) const
{
	if (!has(id))
	{
		throw std::runtime_error("action instance not in brochure; cannot get");
	}

	auto statement = brochure->database->create_statement(
		"SELECT * FROM ActionInstance WHERE id=?;");
	statement.bind(1, id);
	auto iter = const_iterator(*brochure->database, statement);
	return *iter;
}

twoflower::Brochure::Actions::const_iterator::const_iterator(
	Database& database, Statement& statement, bool is_instance) :
	database(&database),
	statement(new Statement(statement)),
	is_instance(is_instance),
	end(false)
{
	next();
}

twoflower::Brochure::Actions::const_iterator::~const_iterator()
{
	// Nothing.
}

twoflower::Brochure::Actions::const_iterator&
twoflower::Brochure::Actions::const_iterator::operator ++()
{
	next();
	return *this;
}

twoflower::Brochure::Actions::const_iterator
twoflower::Brochure::Actions::const_iterator::operator ++(int)
{
	next();
	return *this;
}

bool twoflower::Brochure::Actions::const_iterator::operator ==(
	const const_iterator& other) const
{
	return statement.get() == other.statement.get() || (end && other.end);
}

bool twoflower::Brochure::Actions::const_iterator::operator !=(
	const const_iterator& other) const
{
	return !(*this == other);
}

twoflower::Brochure::Actions::const_iterator::pointer
twoflower::Brochure::Actions::const_iterator::operator ->() const
{
	return &value;
}

twoflower::Brochure::Actions::const_iterator::value_type
twoflower::Brochure::Actions::const_iterator::operator *() const
{
	return value;
}

void twoflower::Brochure::Actions::const_iterator::next()
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
		Action::Builder builder(value);

		if (is_instance)
		{
			int id;
			statement->get("id", id);
			builder.set_id(id);
		}

		Action::Type type;
		if (is_instance)
		{
			int action_definition_id;
			statement->get("action_id", action_definition_id);

			auto name_statement = database->create_statement(
				"SELECT name FROM ActionDefinition WHERE id=?;");
			name_statement.bind(1, action_definition_id);
			name_statement.next();

			type.id = action_definition_id;
			name_statement.get("name", type.name);
		}
		else
		{
			statement->get("id", type.id);
			statement->get("name", type.name);
		}
		builder.set_type(type);

		int getter;
		if (is_instance)
		{
			int action_definition_id;
			statement->get("action_id", action_definition_id);

			auto getter_statement = database->create_statement(
				"SELECT getter FROM ActionDefinition WHERE id=?;");
			getter_statement.bind(1, action_definition_id);
			getter_statement.next();

			getter_statement.get("getter", getter);
		}
		else
		{
			statement->get("getter", getter);
		}
		builder.set_is_getter(getter);

		std::string task;
		if (statement->empty("task") && is_instance)
		{
			int action_definition_id;
			statement->get("action_id", action_definition_id);

			auto task_statement = database->create_statement(
				"SELECT task FROM ActionDefinition WHERE id=?;");
			task_statement.bind(1, action_definition_id);
			task_statement.next();

			task_statement.get("task", task);
		}
		else
		{
			statement->get("task", task);
		}
		builder.set_task(task);

		float cost;
		if (statement->empty("cost") && is_instance)
		{
			int action_definition_id;
			statement->get("action_id", action_definition_id);

			auto cost_statement = database->create_statement(
				"SELECT task FROM ActionDefinition WHERE id=?;");
			cost_statement.bind(1, action_definition_id);
			cost_statement.next();

			cost_statement.get("task", task);

			cost_statement.get(0, cost);
		}
		else
		{
			statement->get("cost", cost);
		}
		builder.set_cost_multiplier(cost);
	}
}
