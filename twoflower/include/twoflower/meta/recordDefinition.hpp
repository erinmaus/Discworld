// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_RECORD_DEFINITION_HPP
#define TWOFLOWER_RECORD_DEFINITION_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace twoflower
{
	class RecordDefinition
	{
	public:
		explicit RecordDefinition(const std::string& name);
		~RecordDefinition() = default;

		enum class Type
		{
			integer,
			text,
			real,
			blob,
			action,
			resource
		};

		const std::string& get_name() const;

		void define(const std::string& column, Type type);

		std::size_t count() const;

		std::string get_name(std::size_t index) const;
		Type get_type(std::size_t index) const;

		std::size_t get_index(const std::string& column) const;
		bool has_index(const std::string& column) const;

	private:
		std::string name;

		static const std::size_t ENTRY_DEFINITION_COLUMN = 0;
		static const std::size_t ENTRY_DEFINITION_TYPE = 1;
		typedef std::tuple<std::string, Type> EntryDefinitionTuple;

		std::vector<EntryDefinitionTuple> entryDefinitions;
		std::unordered_map<std::string, std::size_t> columns;
	};
}

#endif
