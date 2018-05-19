// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cstdio>
#include <stdexcept>
#include "twoflower/brochure.hpp"

int main(int argc, const char* argv[])
{
	twoflower::Brochure brochure(":memory:");
	brochure.create();

	auto mine_action_definition = brochure.create_action_definition("mine");
	std::printf(
		"mine action definition: %d\n",
		(int)mine_action_definition.get_id());
	auto smith_action_definition = brochure.create_action_definition("smith");
	std::printf(
		"smith action definition: %d\n",
		(int)smith_action_definition.get_id());

	try
	{
		brochure.create_action_definition("smith");
	}
	catch(const std::exception& e)
	{
		std::printf("%s\n", e.what());
	}

	try
	{
		brochure.create_action_definition("SMITH");
	}
	catch(const std::exception& e)
	{
		std::printf("%s\n", e.what());
	}

	std::printf("action definitions:\n");
	{
		auto begin = brochure.action_definitions_begin();
		auto end = brochure.action_definitions_end();

		for (auto i = begin; i != end; ++i)
		{
			std::printf(
				"- '%s' (id: %d)\n",
				i->get_name().c_str(),
				(int)i->get_id());
		}
	}

	twoflower::ActionDefinition action_definition1;
	if (brochure.try_get_action_definition(1, action_definition1))
	{
		std::printf("action 1: %s\n", action_definition1.get_name().c_str());
	}
	else
	{
		std::printf("couldn't get action 1\n");
	}

	auto smith_action = brochure.create_action(smith_action_definition);
	std::printf("smith action: %d\n", (int)smith_action.get_id());

	std::printf("actions:\n");
	{
		auto begin = brochure.actions_begin();
		auto end = brochure.actions_end();

		for (auto i = begin; i != end; ++i)
		{
			auto action_definition = brochure.get_action_definition(*i);
			std::printf(
				"- '%s' (id: %d)",
				action_definition.get_name().c_str(),
				(int)i->get_id());
		}
	}

	return 0;
}
