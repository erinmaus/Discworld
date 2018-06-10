// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <functional>
#include "mapp/mapp.hpp"
#include "deps/lua.hpp"
#include "twoflower/brochure.hpp"

template <typename R, typename T>
static typename std::function<sol::optional<R>(sol::this_state)>
mapp_create_iterator(T& begin, T& end)
{
	return [begin, end](sol::this_state S) mutable
	{
		lua_State* L = S;

		if (begin != end)
		{
			auto v = *begin;
			++begin;

			return sol::optional<R>(v);
		}
		else
		{
			return sol::optional<R>();
		}
	};
}

static auto mapp_create_action_definitions_iterator(
	const twoflower::Brochure& brochure)
{
	return mapp_create_iterator<twoflower::ActionDefinition>(
		brochure.action_definitions_begin(),
		brochure.action_definitions_end());
}

static auto mapp_create_actions_iterator(
	const twoflower::Brochure& brochure)
{
	return mapp_create_iterator<twoflower::Action>(
		brochure.actions_begin(),
		brochure.actions_end());
}

static auto mapp_find_actions_by_definition(
	const twoflower::Brochure& brochure,
	const twoflower::ActionDefinition& definition)
{
	return mapp_create_iterator<twoflower::Action>(
		brochure.actions_by_definition(definition),
		brochure.actions_end());
}

static auto mapp_find_actions_by_resource(
	const twoflower::Brochure& brochure,
	const twoflower::Resource& resource)
{
	return mapp_create_iterator<twoflower::Action>(
		brochure.actions_by_resource(resource),
		brochure.actions_end());
}

static auto mapp_create_resource_types_iterator(
	const twoflower::Brochure& brochure)
{
	return mapp_create_iterator<twoflower::ResourceType>(
		brochure.resource_types_begin(),
		brochure.resource_types_end());
}

static auto mapp_create_resources_iterator(
	const twoflower::Brochure& brochure)
{
	return mapp_create_iterator<twoflower::Resource>(
		brochure.resources_begin(),
		brochure.resources_end());
}

static auto mapp_find_resources_by_type(
	const twoflower::Brochure& brochure,
	const twoflower::ResourceType& type)
{
	return mapp_create_iterator<twoflower::Resource>(
		brochure.resources_by_type(type),
		brochure.resources_end());
}

static auto mapp_find_resources_by_name(
	const twoflower::Brochure& brochure,
	const std::string& name)
{
	return mapp_create_iterator<twoflower::Resource>(
		brochure.resources_by_name(name),
		brochure.resources_end());
}

static auto mapp_find_resources_by_name_and_type(
	const twoflower::Brochure& brochure,
	const std::string& name,
	const twoflower::ResourceType& type)
{
	return mapp_create_iterator<twoflower::Resource>(
		brochure.resources_by_name_and_type(name, type),
		brochure.resources_end());
}

static void mapp_connect_action_to_resource(
	twoflower::Brochure& brochure,
	const twoflower::Action& action,
	const twoflower::Resource& resource)
{
	brochure.connect(action, resource);
}

static void mapp_connection_input_to_action(
	twoflower::Brochure& brochure,
	const twoflower::Action& action,
	const twoflower::Resource& resource,
	float quantity)
{
	brochure.connect(
		twoflower::ActionConstraint::Type::input,
		action,
		resource,
		quantity);
}

static void mapp_connection_output_to_action(
	twoflower::Brochure& brochure,
	const twoflower::Action& action,
	const twoflower::Resource& resource,
	float quantity)
{
	brochure.connect(
		twoflower::ActionConstraint::Type::output,
		action,
		resource,
		quantity);
}

static void mapp_connection_requirement_to_action(
	twoflower::Brochure& brochure,
	const twoflower::Action& action,
	const twoflower::Resource& resource,
	float quantity)
{
	brochure.connect(
		twoflower::ActionConstraint::Type::requirement,
		action,
		resource,
		quantity);
}

static auto mapp_get_inputs(
	const twoflower::Brochure& brochure,
	const twoflower::Action& action)
{
	return mapp_create_iterator<twoflower::ActionConstraint>(
		brochure.action_constraints_begin(twoflower::ActionConstraint::Type::input, action),
		brochure.action_constraints_end());
}

static auto mapp_get_outputs(
	const twoflower::Brochure& brochure,
	const twoflower::Action& action)
{
	return mapp_create_iterator<twoflower::ActionConstraint>(
		brochure.action_constraints_begin(twoflower::ActionConstraint::Type::output, action),
		brochure.action_constraints_end());
}

static auto mapp_get_requirements(
	const twoflower::Brochure& brochure,
	const twoflower::Action& action)
{
	return mapp_create_iterator<twoflower::ActionConstraint>(
		brochure.action_constraints_begin(twoflower::ActionConstraint::Type::requirement, action),
		brochure.action_constraints_end());
}

static void mapp_create(twoflower::Brochure& brochure)
{
	brochure.create();
}

static void mapp_create_record(
	twoflower::Brochure& brochure,
	const twoflower::RecordDefinition& definition)
{
	brochure.create(definition);
}

static int mapp_select(lua_State* L)
{
	auto& brochure = sol::stack::get<twoflower::Brochure>(L, 1);
	auto& record_definition = sol::stack::get<twoflower::RecordDefinition>(L, 2);
	auto& query = sol::stack::get<twoflower::Query>(L, 3);
	auto limit = luaL_optint(L, 4, twoflower::Brochure::UNLIMITED_POWER);

	lua_newtable(L);
	int index = 1;
	for (auto& i: brochure.select(record_definition, query, limit))
	{
		lua_pushnumber(L, index);
		sol::stack::push(L, i);
		lua_rawset(L, -3);
	}

	return 1;
}

extern "C"
MAPP_EXPORT int luaopen_mapp_brochure(lua_State* L)
{
	sol::usertype<twoflower::Brochure> T(
		sol::call_constructor, sol::constructors<twoflower::Brochure(), twoflower::Brochure(const std::string&)>(),
		"createActionDefinition", &twoflower::Brochure::create_action_definition,
		"tryGetActionDefinition", sol::overload<bool (twoflower::Brochure::*)(const twoflower::ID&, twoflower::ActionDefinition& result) const, bool (twoflower::Brochure::*)(const std::string&, twoflower::ActionDefinition& result) const>(&twoflower::Brochure::try_get_action_definition, &twoflower::Brochure::try_get_action_definition),
		"actionDefinitions", sol::property(&mapp_create_action_definitions_iterator),
		"createAction", &twoflower::Brochure::create_action,
		"tryGetAction", &twoflower::Brochure::try_get_action,
		"getActionDefinitionFromAction", &twoflower::Brochure::get_action_definition,
		"actions", sol::property(&mapp_create_actions_iterator),
		"findActionsByDefinition", &mapp_find_actions_by_definition,
		"findActionsByResource", &mapp_find_actions_by_resource,
		"createResourceType", &twoflower::Brochure::create_resource_type,
		"tryGetResourceType", sol::overload<bool (twoflower::Brochure::*)(const twoflower::ID&, twoflower::ResourceType& result) const, bool (twoflower::Brochure::*)(const std::string&, twoflower::ResourceType& result) const>(&twoflower::Brochure::try_get_resource_type, &twoflower::Brochure::try_get_resource_type),
		"getResourceTypeFromResource", &twoflower::Brochure::get_resource_type,
		"resourceTypes", &mapp_create_resource_types_iterator,
		"createResource", &twoflower::Brochure::create_resource,
		"tryGetResource", &twoflower::Brochure::try_get_resource,
		"resources", sol::property(&mapp_create_resources_iterator),
		"findResourcesByType", &mapp_find_resources_by_type,
		"findResourcesByName", &mapp_find_resources_by_name,
		"findResourcesByNameAndType", &mapp_find_resources_by_name_and_type,
		"connect", &mapp_connect_action_to_resource,
		"connectInput", &mapp_connection_input_to_action,
		"connectOutput", &mapp_connection_output_to_action,
		"connectRequirement", &mapp_connection_requirement_to_action,
		"getInputs", &mapp_get_inputs,
		"getOutputs", &mapp_get_outputs,
		"getRequirements", &mapp_get_requirements,
		"getConstraintResource", &twoflower::Brochure::get_constraint_resource,
		"getConstraintAction", &twoflower::Brochure::get_constraint_action,
		"create", &mapp_create,
		"createRecord", &mapp_create_record,
		"insert", &twoflower::Brochure::insert,
		"select", &mapp_select,
		"select_one", &twoflower::Brochure::select_one
	);

	sol::stack::push(L, T);

	return 1;
}
