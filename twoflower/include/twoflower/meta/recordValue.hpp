// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_RECORD_VALUE_HPP
#define TWOFLOWER_RECORD_VALUE_HPP

#include <cstdint>
#include <variant>
#include <vector>
#include "twoflower/meta/recordDefinition.hpp"
#include "twoflower/relationships/action.hpp"
#include "twoflower/relationships/resource.hpp"

namespace twoflower
{
	class RecordValue
	{
	public:
		RecordValue() = default;
		~RecordValue() = default;

		void set(int value);
		void set(float value);
		void set(const std::string& value);
		void set(const std::vector<std::uint8_t>& value);
		void set(const Action& action);
		void set(const Resource& action);

		bool get(int& result);
		bool get(float& result);
		bool get(std::string& result);
		bool get(std::vector<std::uint8_t>& result);
		bool get(Action& result);
		bool get(Resource& result);

		RecordDefinition::Type get_type() const;

		void make_default(RecordDefinition::Type type);

	private:
		RecordDefinition::Type type = RecordDefinition::Type::integer;

		typedef std::variant<
			int,
			float,
			std::string,
			std::vector<std::uint8_t>,
			Action,
			Resource> InstanceType;

		InstanceType instance;
	};
}

#endif
