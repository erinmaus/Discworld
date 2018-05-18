// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_ACTION_HPP
#define TWOFLOWER_ACTION_HPP

#include <string>
#include "twoflower/id.hpp"
#include "twoflower/relationships/actionDefinition.hpp"

namespace twoflower
{
	class Action
	{
	public:
		Action() = default;
		Action(const ID& id, const ActionDefinition& action_definition);
		~Action() = default;

		const ID& get_id() const;
		void set_id(const ID& value);

		const ActionDefinition& get_action_definition() const;
		void set_action_definition(const ActionDefinition& value);

	private:
		ID id;
		ActionDefinition action_definition;
	};
}

#endif
