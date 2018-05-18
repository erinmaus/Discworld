// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_ACTION_DEFINITION_HPP
#define TWOFLOWER_ACTION_DEFINITION_HPP

#include <string>
#include "twoflower/id.hpp"

namespace twoflower
{
	class ActionDefinition
	{
	public:
		ActionDefinition() = default;
		ActionDefinition(const ID& id, const std::string& name);
		~ActionDefinition() = default;

		const ID& get_id() const;
		void set_id(const ID& value);

		const std::string& get_name() const;
		void set_name(const std::string& value);

	private:
		ID id;
		std::string name;
	};
}

#endif
