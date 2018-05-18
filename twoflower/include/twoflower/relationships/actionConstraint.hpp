// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_ACTION_CONSTRAINT_HPP
#define TWOFLOWER_ACTION_CONSTRAINT_HPP

#include "twoflower/id.hpp"
#include "twoflower/relationships/action.hpp"
#include "twoflower/relationships/resource.hpp"

namespace twoflower
{
	class ActionConstraint
	{
	public:
		enum class Type
		{
			input,
			output,
			requirement
		};

		ActionConstraint() = default;
		ActionConstraint(
			const ID& id,
			Type type,
			const Action& action,
			const Resource& resource,
			float count);
		~ActionConstraint() = default;

		const ID& get_id() const;
		void set_id(const ID& value);

		Type get_type() const;
		void set_type(Type type);

		const Action& get_action() const;
		void set_action(const Action& value);

		const Resource& get_resource() const;
		void set_resource(const Resource& value);

		float get_count() const;
		void set_count(float value);

	private:
		ID id;
		Type type;
		Action action;
		Resource resource;
		float count;
	};
}

#endif
