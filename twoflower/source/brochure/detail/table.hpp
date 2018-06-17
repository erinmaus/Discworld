// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_DETAIL_BROCHURE_TABLE_HPP
#define TWOFLOWER_DETAIL_BROCHURE_TABLE_HPP

#include <map>
#include <set>
#include <tuple>
#include <string>
#include "twoflower/brochure.hpp"

namespace twoflower
{
	class Brochure::Table
	{
	public:
		explicit Table(const std::string& name);
		Table(const std::string& name, const Table& table);
		~Table() = default;

		const std::string& get_name() const;

		enum class Type
		{
			integer,
			text,
			real,
			blob
		};
		void add_primary_key(const std::string& name, Type type);
		void add_column(
			const std::string& name,
			Type type,
			bool nullable,
			bool unique);

		void bind_foreign_key(
			const std::string& other_table,
			const std::string& self_column,
			const std::string& reference_column);

		void create(Brochure::Database& database) const;

	private:
		static std::string get_type_literal(Type type);

		std::string name;

		typedef std::map<std::string, std::pair<std::string, std::string>> ForeignKeys;
		ForeignKeys foreign_keys;

		static const std::size_t COLUMN_NAME = 0;
		static const std::size_t COLUMN_TYPE = 1;
		static const std::size_t COLUMN_NULLABLE = 2;
		static const std::size_t COLUMN_UNIQUE = 3;
		typedef std::tuple<std::string, Type, bool, bool> Column;
		typedef std::set<Column> Columns;
		Columns columns;
		Columns primary_keys;
	};
}

#endif
