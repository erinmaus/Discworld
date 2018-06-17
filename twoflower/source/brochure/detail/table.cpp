// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <sstream>
#include "database.hpp"
#include "statement.hpp"
#include "table.hpp"

const std::size_t twoflower::Brochure::Table::COLUMN_NAME;
const std::size_t twoflower::Brochure::Table::COLUMN_TYPE;
const std::size_t twoflower::Brochure::Table::COLUMN_NULLABLE;

twoflower::Brochure::Table::Table(const std::string& name) :
	name(name)
{
	// Nothing.
}

twoflower::Brochure::Table::Table(const std::string& name, const Table& table)
{
	*this = table;
	this->name = name;
}

const std::string& twoflower::Brochure::Table::get_name() const
{
	return name;
}

void twoflower::Brochure::Table::add_primary_key(
	const std::string& name,
	Type type)
{
	primary_keys.emplace(name, type, false, false);
}

void twoflower::Brochure::Table::add_column(
	const std::string& name,
	Type type,
	bool nullable,
	bool unique)
{
	columns.emplace(name, type, nullable, unique);
}

void twoflower::Brochure::Table::bind_foreign_key(
	const std::string& other_table,
	const std::string& self_column,
	const std::string& reference_column)
{
	foreign_keys.emplace(self_column, std::make_pair(other_table, reference_column));
}

void twoflower::Brochure::Table::create(Brochure::Database& database) const
{
	std::stringstream stream;
	stream << "CREATE TABLE" << " " << name << " " << "(" << std::endl;

	for (auto& primary_key: primary_keys)
	{
		auto name = std::get<COLUMN_NAME>(primary_key);
		auto type = std::get<COLUMN_TYPE>(primary_key);
		stream << "\t" << name << " " << get_type_literal(type) << " " << "NOT NULL";
		stream << "," << std::endl;
	}

	for (auto& column: columns)
	{
		auto name = std::get<COLUMN_NAME>(column);
		auto type = std::get<COLUMN_TYPE>(column);
		auto nullable = std::get<COLUMN_NULLABLE>(column);
		auto unique = std::get<COLUMN_UNIQUE>(column);
		stream << "\t" << name << " " << get_type_literal(type);

		if (!nullable)
		{
			stream << " " << "NOT NULL";
		}

		if (unique)
		{
			stream << " " << "UNIQUE";
		}

		if (type == Type::text)
		{
			stream << " " << "COLLATE NOCASE";
		}

		stream << "," << std::endl;
	}

	stream << "\t" << "PRIMARY KEY" << " " << "(";
	std::size_t index = 1;
	for (auto& primary_key: primary_keys)
	{
		auto name = std::get<COLUMN_NAME>(primary_key);
		stream << name;

		if (index < primary_keys.size())
		{
			stream << "," << " ";
		}
		++index;
	}
	stream << ")";

	if (!foreign_keys.empty())
	{
		stream << "," << std::endl;

		index = 1;
		for (auto& i: foreign_keys)
		{
			auto& column = i.first;
			auto& foreign_table = i.second.first;
			auto& foreign_key = i.second.second;
			std::size_t reference_index;

			stream << "\t" << "FOREIGN KEY" << " " << "(";
			
			stream << column;

			stream << ")" << " " << "REFERENCES" << " " << foreign_table << "(";

			stream << foreign_key;

			stream << ")" << " " << "ON DELETE CASCADE";

			if (index < foreign_keys.size())
			{
				stream << ",";
			}
			++index;

			stream << std::endl;
		}
	}

	stream << std::endl;
	stream << ")" << ";";

	auto statement = database.create_statement(stream.str());
	statement.execute();
}

std::string twoflower::Brochure::Table::get_type_literal(Type type)
{
	if (type == Type::integer)
	{
		return "INTEGER";
	}
	else if (type == Type::text)
	{
		return "TEXT";
	}
	else if (type == Type::real)
	{
		return "REAL";
	}
	else if (type == Type::blob)
	{
		return "BLOB";
	}
	else
	{
		// I don't know why having to add this makes me so angry.
		//
		// Don't pass garbage arguments, duh!
		throw std::runtime_error(
			"Type enumeration has invalid value;"
			" thus, no corresponding literal.");
	}
}
