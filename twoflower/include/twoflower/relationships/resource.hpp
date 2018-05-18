// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_RESOURCE_HPP
#define TWOFLOWER_RESOURCE_HPP

#include <string>
#include "twoflower/id.hpp"
#include "twoflower/relationships/resourceType.hpp"

namespace twoflower
{
	class Resource
	{
	public:
		Resource() = default;
		Resource(
			const ID& id,
			const std::string& name,
			const ResourceType& resource_type,
			bool singleton);
		~Resource() = default;

		const ID& get_id() const;
		void set_id(const ID& value);

		const std::string& get_name() const;
		void set_name(const std::string& value);

		const ResourceType& get_resource_type() const;
		void set_resource_type(const ResourceType& value);

		bool get_is_singleton() const;
		void set_is_singleton(bool value);

	private:
		ID id;
		std::string name;
		ResourceType resource_type;
		bool is_singleton;
	};
}

#endif
