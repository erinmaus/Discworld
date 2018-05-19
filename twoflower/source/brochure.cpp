// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cassert>
#include <stdexcept>
#include "twoflower/brochure.hpp"
#include "brochure/detail/database.hpp"
#include "brochure/detail/statement.hpp"
#include "brochure/detail/table.hpp"

twoflower::Brochure::Brochure(const std::string& filename)
{
	database = std::make_shared<Database>(filename);
}

twoflower::Brochure::~Brochure()
{
	// Nothing.
}

twoflower::ActionDefinition twoflower::Brochure::create_action_definition(
	const std::string& name)
{
	ActionDefinition result;

	auto statement = database->create_statement(
		"INSERT INTO ActionDefinition(name)"
		" VALUES (?);");
	statement.bind(1, name);
	statement.execute();

	auto id_statement = database->create_statement(
		"SELECT last_insert_rowid();");
	id_statement.next();

	int id;
	id_statement.get(0, id);

	result.set_id(id);
	result.set_name(name);

	return result;
}

bool twoflower::Brochure::try_get_action_definition(
	const ID& id,
	ActionDefinition& result) const
{
	auto statement = database->create_statement(
		"SELECT name FROM ActionDefinition WHERE id = ?;");
	statement.bind(1, (int)id);

	if (statement.next())
	{
		result.set_id((int)id);

		std::string name;
		statement.get("name", name);
		result.set_name(name);

		return true;
	}
	else
	{
		return false;
	}
}

twoflower::Brochure::Iterator<twoflower::ActionDefinition>
twoflower::Brochure::action_definitions_begin() const
{
	auto statement = database->create_statement(
		"SELECT * FROM ActionDefinition;");
	return Iterator<ActionDefinition>(*this, statement);
}

twoflower::Brochure::Iterator<twoflower::ActionDefinition>
twoflower::Brochure::action_definitions_end() const
{
	return Iterator<ActionDefinition>();
}

twoflower::Action twoflower::Brochure::create_action(
	const ActionDefinition& action_definition)
{
	twoflower::Action result;
	auto statement = database->create_statement(
		"INSERT INTO Action(action_definition_id)"
		" VALUES (?);");
	statement.bind(1, (int)action_definition.get_id());

	statement.execute();

	auto id_statement = database->create_statement(
		"SELECT last_insert_rowid();");
	id_statement.next();

	int id;
	id_statement.get(0, id);

	result.set_id(id);

	return result;
}

bool twoflower::Brochure::try_get_action(const ID& id, Action& result)
{
	auto statement = database->create_statement(
		"SELECT 1 FROM Action WHERE id = ?;");
	statement.bind(1, (int)id);

	if (statement.next())
	{
		result.set_id(id);
		return true;
	}
	else
	{
		return false;
	}
}

twoflower::ActionDefinition twoflower::Brochure::get_action_definition(
	const Action& action)
{
	ActionDefinition result;

	auto statement = database->create_statement(
		"SELECT action_definition_id FROM Action WHERE id = ?;");
	statement.bind(1, (int)action.get_id());

	if (statement.next())
	{
		int id;
		statement.get("action_definition_id", id);

		if (try_get_action_definition(id, result))
		{
			return result;
		}
	}

	throw std::runtime_error("action does not exist in brochure");
}

twoflower::Brochure::Iterator<twoflower::Action>
twoflower::Brochure::actions_begin() const
{
	auto statement = database->create_statement(
		"SELECT id FROM Action;");
	return Iterator<Action>(*this, statement);
}

twoflower::Brochure::Iterator<twoflower::Action>
twoflower::Brochure::actions_end() const
{
	return Iterator<Action>();
}

twoflower::Brochure::Iterator<twoflower::Action>
twoflower::Brochure::actions_by_definition(
	const ActionDefinition& action_definition) const
{
	auto statement = database->create_statement(
		"SELECT id FROM Action WHERE action_definition_id = ?;");
	statement.bind(1, (int)action_definition.get_id());
	return Iterator<Action>(*this, statement);
}

void twoflower::Brochure::create()
{
	Table action_definition("ActionDefinition");
	action_definition.add_primary_key("id", Table::Type::integer);
	action_definition.add_column("name", Table::Type::text, false, true);
	action_definition.create(*database);

	Table action("Action");
	action.add_primary_key("id", Table::Type::integer);
	action.add_column("action_definition_id", Table::Type::integer, false, false);
	action.bind_foreign_key(
		"ActionDefinition",
		"action_definition_id",
		"id");
	action.create(*database);

	Table resource_type("ResourceType");
	resource_type.add_primary_key("id", Table::Type::integer);
	resource_type.add_column("name", Table::Type::text, false, true);
	resource_type.create(*database);

	Table resource("Resource");
	resource.add_primary_key("id", Table::Type::integer);
	resource.add_column("resource_type_id", Table::Type::integer, false, false);
	resource.add_column("name", Table::Type::text, false, true);
	resource.add_column("singleton", Table::Type::integer, false, false);
	resource.bind_foreign_key(
		"ResourceType",
		"resource_type_id",
		"id");
	resource.create(*database);

	Table resources_actions("ResourcesActions");
	resources_actions.add_primary_key("resource_id", Table::Type::integer);
	resources_actions.add_primary_key("action_id", Table::Type::integer);
	resources_actions.bind_foreign_key(
		"Resource",
		"resource_id",
		"id");
	resources_actions.bind_foreign_key(
		"Action",
		"action_id",
		"id");
	resources_actions.create(*database);

	Table action_constraint("ActionConstraint");
	action_constraint.add_primary_key("id", Table::Type::integer);
	action_constraint.add_column("resource_id", Table::Type::integer, false, false);
	action_constraint.add_column("action_id", Table::Type::integer, false, false);
	action_constraint.add_column("count", Table::Type::real, false, false);
	action_constraint.bind_foreign_key(
		"Resource",
		"resource_id",
		"id");
	action_constraint.bind_foreign_key(
		"Action",
		"action_id",
		"id");

	Table action_input("ActionInput", action_constraint);
	action_input.create(*database);

	Table action_output("ActionOutput", action_constraint);
	action_output.create(*database);

	Table action_requirement("ActionRequirement", action_constraint);
	action_requirement.create(*database);
}

bool twoflower::Brochure::IteratorImpl<twoflower::ActionDefinition>::next(
	Statement& statement,
	ActionDefinition& value)
{
	if (!statement.next())
	{
		return false;
	}
	else
	{
		int id;
		statement.get("id", id);

		std::string name;
		statement.get("name", name);

		value.set_id(id);
		value.set_name(name);

		return true;
	}
}

bool twoflower::Brochure::IteratorImpl<twoflower::Action>::next(
	Statement& statement,
	Action& value)
{
	if (!statement.next())
	{
		return false;
	}
	else
	{
		int id;
		statement.get("id", id);

		value.set_id(id);

		return true;
	}
}
