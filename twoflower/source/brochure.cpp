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
