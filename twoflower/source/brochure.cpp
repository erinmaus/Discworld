// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cassert>
#include <stdexcept>
#include <sstream>
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

bool twoflower::Brochure::try_get_action(const ID& id, Action& result) const
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
	const Action& action) const
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

twoflower::Brochure::Iterator<twoflower::Action>
twoflower::Brochure::actions_by_resource(
	const Resource& resource) const
{
	auto statement = database->create_statement(
		"SELECT id FROM Action"
		" INNER JOIN ResourcesActions"
		" ON ResourcesActions.resource_id = ?"
		" AND ResourcesActions.action_id = Action.id;");
	statement.bind(1, (int)resource.get_id());
	return Iterator<Action>(*this, statement);
}

twoflower::ResourceType twoflower::Brochure::create_resource_type(
	const std::string& name)
{
	ResourceType result;

	auto statement = database->create_statement(
		"INSERT INTO ResourceType(name)"
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

bool twoflower::Brochure::try_get_resource_type(
	const ID& id,
	ResourceType& result) const
{
	auto statement = database->create_statement(
		"SELECT name FROM ResourceType WHERE id = ?;");
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

twoflower::Brochure::Iterator<twoflower::ResourceType>
twoflower::Brochure::resource_types_begin() const
{
	auto statement = database->create_statement(
		"SELECT * FROM ResourceType;");
	return Iterator<ResourceType>(*this, statement);
}

twoflower::Brochure::Iterator<twoflower::ResourceType>
twoflower::Brochure::resource_types_end() const
{
	return Iterator<ResourceType>();
}

twoflower::Resource twoflower::Brochure::create_resource(
	const ResourceType& resource_type,
	const std::string& name,
	bool is_singleton)
{
	twoflower::Resource result;
	auto statement = database->create_statement(
		"INSERT INTO Resource(resource_type_id, name, singleton)"
		" VALUES (?, ?, ?);");
	statement.bind(1, (int)resource_type.get_id());
	statement.bind(2, name);
	statement.bind(3, is_singleton);

	statement.execute();

	auto id_statement = database->create_statement(
		"SELECT last_insert_rowid();");
	id_statement.next();

	int id;
	id_statement.get(0, id);

	result.set_id(id);
	result.set_name(name);
	result.set_is_singleton(is_singleton);

	return result;
}

bool twoflower::Brochure::try_get_resource(const ID& id, Resource& result) const
{
	auto statement = database->create_statement(
		"SELECT name, singleton FROM Resource WHERE id = ?;");
	statement.bind(1, (int)id);

	if (statement.next())
	{
		std::string name;
		statement.get("name", name);

		int is_singleton;
		statement.get("singleton", is_singleton);

		result.set_id(id);
		result.set_name(name);
		result.set_is_singleton(is_singleton);

		return true;
	}
	else
	{
		return false;
	}
}

twoflower::ResourceType twoflower::Brochure::get_resource_type(
	const Resource& resource) const
{
	ResourceType result;

	auto statement = database->create_statement(
		"SELECT resource_type_id FROM Resource WHERE id = ?;");
	statement.bind(1, (int)resource.get_id());

	if (statement.next())
	{
		int id;
		statement.get("resource_type_id", id);

		if (try_get_resource_type(id, result))
		{
			return result;
		}
	}

	throw std::runtime_error("resource does not exist in brochure");
}

twoflower::Brochure::Iterator<twoflower::Resource>
twoflower::Brochure::resources_begin() const
{
	auto statement = database->create_statement(
		"SELECT name, singleton FROM Resource;");
	return Iterator<Resource>(*this, statement);
}

twoflower::Brochure::Iterator<twoflower::Resource>
twoflower::Brochure::resources_end() const
{
	return Iterator<Resource>();
}

twoflower::Brochure::Iterator<twoflower::Resource>
twoflower::Brochure::resources_by_type(
	const ResourceType& resource_type) const
{
	auto statement = database->create_statement(
		"SELECT name, singleton FROM Resource WHERE resource_type_id = ?;");
	statement.bind(1, (int)resource_type.get_id());
	return Iterator<Resource>(*this, statement);
}

void twoflower::Brochure::connect(
	const Action& action,
	const Resource& resource)
{
	auto statement = database->create_statement(
		"INSERT INTO ResourcesActions (resource_id, action_id)"
		" VALUES(?, ?);");
	statement.bind(1, (int)action.get_id());
	statement.bind(2, (int)resource.get_id());

	statement.execute();
}

void twoflower::Brochure::connect(
	ActionConstraint::Type type,
	const Action& action,
	const Resource& resource,
	float quantity)
{
	std::stringstream query;

	query << "INSERT INTO ";
	query << constraint_type_to_table_name(type);

	query << "(resource_id, action_id, count)";
	query << " VALUES(?, ?, ?);";

	auto statement = database->create_statement(query.str());
	statement.bind(1, (int)resource.get_id());
	statement.bind(2, (int)action.get_id());
	statement.bind(3, quantity);

	statement.execute();
}

twoflower::Brochure::Iterator<twoflower::ActionConstraint>
twoflower::Brochure::action_constraints_begin(
	ActionConstraint::Type type,
	const Action& action) const
{
	std::stringstream query;
	query << "SELECT id, count FROM ";
	query << constraint_type_to_table_name(type);
	query << " WHERE action_id = ?;";

	auto statement = database->create_statement(query.str());
	statement.bind(1, (int)action.get_id());

	return Iterator<twoflower::ActionConstraint>(
		*this,
		statement,
		ActionConstraint(type));
}

twoflower::Brochure::Iterator<twoflower::ActionConstraint>
twoflower::Brochure::action_constraints_end() const
{
	return Iterator<twoflower::ActionConstraint>();
}

twoflower::Action twoflower::Brochure::get_constraint_action(
	const ActionConstraint& constraint) const
{
	std::stringstream query;
	query << "SELECT action_id FROM ";
	query << constraint_type_to_table_name(constraint.get_type());
	query << " WHERE id = ?;";

	auto statement = database->create_statement(query.str());
	statement.bind(1, (int)constraint.get_id());

	if (statement.next())
	{
		int id;
		statement.get("action_id", id);

		twoflower::Action result;
		if (try_get_action(id, result))
		{
			return result;
		}
	}

	throw std::runtime_error("bad logic! missing action for constraint");
}

twoflower::Resource twoflower::Brochure::get_constraint_resource(
	const ActionConstraint& constraint) const
{
	std::stringstream query;
	query << "SELECT resource_id FROM ";
	query << constraint_type_to_table_name(constraint.get_type());
	query << " WHERE id = ?;";

	auto statement = database->create_statement(query.str());
	statement.bind(1, (int)constraint.get_id());

	if (statement.next())
	{
		int id;
		statement.get("resource_id", id);

		twoflower::Resource result;
		if (try_get_resource(id, result))
		{
			return result;
		}
	}

	throw std::runtime_error("bad logic! missing resource for constraint");
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
	resource.add_column("name", Table::Type::text, false, false);
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

void twoflower::Brochure::create(const RecordDefinition& record)
{
	assert(record.count() > 0 && "record malformed");

	Table table(std::string("meta_") + record.get_name());

	// Column 0 is always the primary key.
	table.add_primary_key(
		record.get_name(0),
		(Table::Type)record_definition_type_to_table_type(record.get_type(0)));

	// Since we added Column 0 as primary key, start at Column 1.
	for (std::size_t i = 1; i < record.count(); ++i)
	{
		table.add_column(
			record.get_name(i),
			(Table::Type)record_definition_type_to_table_type(record.get_type(i)),
			true,
			false);

		switch (record.get_type(i))
		{
			case RecordDefinition::Type::resource:
				table.bind_foreign_key("Resource", record.get_name(i), "id");
				break;
			case RecordDefinition::Type::action:
				table.bind_foreign_key("Action", record.get_name(i), "id");
				break;
		}
	}

	table.create(*database);
}

void twoflower::Brochure::insert(
	const RecordDefinition& definition,
	const Record& record)
{
	std::stringstream query;
	query << "INSERT INTO meta_" << definition.get_name();

	query << "(";
	for (std::size_t i = 1; i < definition.count(); ++i)
	{
		query << definition.get_name(i);
		if (i + 1 < definition.count())
		{
			query << ", ";
		}
	}
	query << ")";

	query << " VALUES (";
	for (std::size_t i = 1; i < definition.count(); ++i)
	{
		query << "?";
		if (i + 1 < definition.count())
		{
			query << ", ";
		}
	}
	query << ");";

	auto statement = database->create_statement(query.str());
	for (std::size_t i = 1; i < definition.count(); ++i)
	{
		RecordValue column_value;
		if (!record.get(i, column_value))
		{
			column_value.make_default(definition.get_type(i));
		}

		statement.bind((int)i, column_value);
	}

	statement.execute();
}

std::vector<twoflower::Record> twoflower::Brochure::select(
	const RecordDefinition& definition,
	const Query& query,
	int limit) const
{
	std::stringstream query_statement;
	{
		query_statement << "SELECT * FROM meta_" << definition.get_name();

		if (!query.empty())
		{
			query_statement << " WHERE";

			auto current = query.begin();
			while (current != query.end())
			{
				query_statement << " " << definition.get_name(current->first) << " = ?";

				++current;

				if (current != query.end())
				{
					query_statement << " AND";
				}
			}
		}

		if (limit != UNLIMITED_POWER)
		{
			query_statement << " LIMIT " << limit;
		}

		query_statement << ";";
	}

	auto statement = database->create_statement(query_statement.str());
	{
		int index = 1;
		for (auto i = query.begin(); i != query.end(); ++i)
		{
			statement.bind(index, i->second);
			++index;
		}
	}

	std::vector<Record> results;
	while (statement.next())
	{
		auto& record = results.emplace_back(definition);
		statement_to_record(statement, definition, record);
	}

	return results;
}

twoflower::Record twoflower::Brochure::select_one(
	const RecordDefinition& definition,
	const Query& query) const
{
	std::vector<Record> results;
	results = select(definition, query, 1);

	if (results.size() > 0)
	{
		return results[0];
	}

	return Record(definition);
}

void twoflower::Brochure::statement_to_record(
	const Statement& statement,
	const RecordDefinition& definition,
	Record& result) const
{
	for (std::size_t i = 0; i < definition.count(); ++i)
	{
		RecordValue value;

		switch (definition.get_type(i))
		{
			case RecordDefinition::Type::integer:
				{
					int v;
					statement.get(definition.get_name(i), v);
					value.set(v);
				}
				break;
			case RecordDefinition::Type::text:
				{
					std::string v;
					statement.get(definition.get_name(i), v);
					value.set(v);
				}
				break;
			case RecordDefinition::Type::real:
				{
					float v;
					statement.get(definition.get_name(i), v);
					value.set(v);
				}
				break;
			case RecordDefinition::Type::blob:
				{
					std::vector<std::uint8_t> v;
					statement.get(definition.get_name(i), v);
					value.set(v);
				}
				break;
			case RecordDefinition::Type::action:
				{
					int id;
					statement.get(definition.get_name(i), id);

					Action v;
					if (try_get_action(id, v))
					{
						value.set(v);
					}
					else
					{
						value.make_default(RecordDefinition::Type::action);
					}
				}
				break;
			case RecordDefinition::Type::resource:
				{
					int id;
					statement.get(definition.get_name(i), id);

					Resource v;
					if (try_get_resource(id, v))
					{
						value.set(v);
					}
					else
					{
						value.make_default(RecordDefinition::Type::resource);
					}
				}
				break;
			default:
				throw std::runtime_error("unhandled record column type");
		}

		result.set(i, value);
	}
}

// Returning the Table::Type cast to an int is a terrible hack.
// We can't expose the internal type Brochure::Table in the public
// header... Thus, we need an intermediate type that *is* public as
// the return type. An integer works for this purpose.
//
// It just involves a lot of ugly casting...
int twoflower::Brochure::record_definition_type_to_table_type(
	twoflower::RecordDefinition::Type type)
{
	switch (type)
	{
		case twoflower::RecordDefinition::Type::integer:
		case twoflower::RecordDefinition::Type::action:
		case twoflower::RecordDefinition::Type::resource:
			return (int)twoflower::Brochure::Table::Type::integer;
		case twoflower::RecordDefinition::Type::text:
			return (int)twoflower::Brochure::Table::Type::text;
		case twoflower::RecordDefinition::Type::real:
			return (int)twoflower::Brochure::Table::Type::real;
		case twoflower::RecordDefinition::Type::blob:
			return (int)twoflower::Brochure::Table::Type::blob;
		default:
			throw std::runtime_error("unrecognized record type");
	}
}

std::string twoflower::Brochure::constraint_type_to_table_name(
	ActionConstraint::Type type)
{
	switch (type)
	{
		case ActionConstraint::Type::input:
			return "ActionInput";
			break;
		case ActionConstraint::Type::output:
			return "ActionOutput";
			break;
		case ActionConstraint::Type::requirement:
			return "ActionRequirement";
			break;
		default:
			throw std::runtime_error(
				"unknown action constraint type;"
				" expected input, output, or requirement.");
	}
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

bool twoflower::Brochure::IteratorImpl<twoflower::ResourceType>::next(
	Statement& statement,
	ResourceType& value)
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

bool twoflower::Brochure::IteratorImpl<twoflower::Resource>::next(
	Statement& statement,
	Resource& value)
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

		int is_singleton;
		statement.get("singleton", is_singleton);

		value.set_id(id);
		value.set_name(name);
		value.set_is_singleton(is_singleton);

		return true;
	}
}

bool twoflower::Brochure::IteratorImpl<twoflower::ActionConstraint>::next(
	Statement& statement,
	ActionConstraint& value)
{
	if (!statement.next())
	{
		return false;
	}
	else
	{
		int id;
		statement.get("id", id);

		float count;
		statement.get("count", count);

		value.set_id(id);
		value.set_count(count);

		return true;
	}
}
