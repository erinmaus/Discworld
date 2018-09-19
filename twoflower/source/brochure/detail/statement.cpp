// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cassert>
#include <cstring>
#include "sqlite3.h"
#include "twoflower/relationships/action.hpp"
#include "twoflower/relationships/resource.hpp"
#include "statement.hpp"

twoflower::Brochure::Statement::Statement(sqlite3* database, const std::string& query) :
	database(database)
{
	sqlite3_stmt* s;
	auto result = sqlite3_prepare(database, query.c_str(), (int)query.length(), &s, nullptr);
	if (result != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}

	statement = std::shared_ptr<sqlite3_stmt>(s, [](auto s) { sqlite3_finalize(s); });
}

twoflower::Brochure::Statement::~Statement()
{
	// Nothing.
}

void twoflower::Brochure::Statement::bind(const std::string& parameter, int value)
{
	bind(sqlite3_bind_parameter_index(statement.get(), parameter.c_str()), value);
}

void twoflower::Brochure::Statement::bind(int parameter, int value)
{
	if (parameter == 0)
	{
		return;
	}

	auto result = sqlite3_bind_int(statement.get(), parameter, value);
	if (result != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}
}

void twoflower::Brochure::Statement::bind(const std::string& parameter, float value)
{
	bind(sqlite3_bind_parameter_index(statement.get(), parameter.c_str()), value);
}

void twoflower::Brochure::Statement::bind(int parameter, float value)
{
	if (parameter == 0)
	{
		return;
	}

	auto result = sqlite3_bind_double(statement.get(), parameter, value);
	if (result != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}
}

void twoflower::Brochure::Statement::bind(const std::string& parameter, const std::string& value)
{
	bind(sqlite3_bind_parameter_index(statement.get(), parameter.c_str()), value);
}

void twoflower::Brochure::Statement::bind(int parameter, const std::string& value)
{
	if (parameter == 0)
	{
		return;
	}

	auto result = sqlite3_bind_text(
		statement.get(), parameter,
		value.c_str(), (int)value.length(),
		SQLITE_TRANSIENT);
	if (result != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}
}

void twoflower::Brochure::Statement::bind(const std::string& parameter, const std::vector<std::uint8_t>& value)
{
	bind(sqlite3_bind_parameter_index(statement.get(), parameter.c_str()), value);
}

void twoflower::Brochure::Statement::bind(int parameter, const std::vector<std::uint8_t>& value)
{
	if (parameter == 0)
	{
		return;
	}

	auto result = sqlite3_bind_blob(
		statement.get(), parameter,
		&value[0], (int)value.size(),
		SQLITE_TRANSIENT);
	if (result != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}
}

void twoflower::Brochure::Statement::bind(const std::string& parameter, const RecordValue& value)
{
	bind(sqlite3_bind_parameter_index(statement.get(), parameter.c_str()), value);
}

void twoflower::Brochure::Statement::bind(int parameter, const RecordValue& value)
{
	switch (value.get_type())
	{
		case RecordDefinition::Type::integer:
			{
				int v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (integer)");

				bind(parameter, v);
			}
			break;
		case RecordDefinition::Type::real:
			{
				float v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (real)");

				bind(parameter, v);
			}
			break;
		case RecordDefinition::Type::text:
			{
				std::string v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (text)");

				bind(parameter, v);
			}
			break;
		case RecordDefinition::Type::blob:
			{
				std::vector<std::uint8_t> v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (text)");

				bind(parameter, v);
			}
			break;
		case RecordDefinition::Type::action:
			{
				Action v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (Action)");

				bind(parameter, (int)v.get_id());
			}
			break;
		case RecordDefinition::Type::resource:
			{
				Resource v;
				bool success = value.get(v);
				assert(success && "RecordValue type/value mismatch (Resource)");

				bind(parameter, (int)v.get_id());
			}
			break;
		default:
			throw std::runtime_error("unknown RecordValue type");
	}
}

int twoflower::Brochure::Statement::execute()
{
	int count = 0;
	while (next())
	{
		++count;
	}

	return count;
}

bool twoflower::Brochure::Statement::next()
{
	if (is_done)
	{
		sqlite3_reset(statement.get());
		is_done = false;
	}

	auto result = sqlite3_step(statement.get());
	if (result == SQLITE_DONE)
	{
		is_done = true;
		return false;
	}
	else if (result != SQLITE_ROW)
	{
		throw std::runtime_error(sqlite3_errmsg(database));
	}

	return true;
}

void twoflower::Brochure::Statement::get(const std::string& column, int& value) const
{
	return get(get_column_index(column), value);
}

void twoflower::Brochure::Statement::get(int column, int& value) const
{
	value = sqlite3_column_int(statement.get(), column);
}

void twoflower::Brochure::Statement::get(const std::string& column, float& value) const
{
	return get(get_column_index(column), value);
}

void twoflower::Brochure::Statement::get(int column, float& value) const
{
	value = (float)sqlite3_column_double(statement.get(), column);
}

void twoflower::Brochure::Statement::get(const std::string& column, std::string& value) const
{
	return get(get_column_index(column), value);
}

void twoflower::Brochure::Statement::get(int column, std::string& value) const
{
	auto result = sqlite3_column_text(statement.get(), column);
	if (result == nullptr)
	{
		value = std::string();
	}
	else
	{
		value = (const char*)result;
	}
}

void twoflower::Brochure::Statement::get(const std::string& column, std::vector<std::uint8_t>& value) const
{
	return get(get_column_index(column), value);
}

void twoflower::Brochure::Statement::get(int column, std::vector<std::uint8_t>& value) const
{
	auto result = sqlite3_column_blob(statement.get(), column);
	if (result == nullptr)
	{
		value = std::vector<std::uint8_t>();
	}
	else
	{
		std::size_t num_bytes = sqlite3_column_bytes(statement.get(), column);
		value.resize(num_bytes);
		std::memcpy(&value[0], result, num_bytes);
	}
}

bool twoflower::Brochure::Statement::empty(const std::string& column) const
{
	return empty(get_column_index(column));
}

bool twoflower::Brochure::Statement::empty(int column) const
{
	return sqlite3_column_type(statement.get(), column) == SQLITE_NULL;
}

int twoflower::Brochure::Statement::get_column_index(const std::string& column) const
{
	for (int i = 0; i < sqlite3_column_count(statement.get()); ++i)
	{
		auto name = sqlite3_column_name(statement.get(), i);
		if (name != nullptr && column == name)
		{
			return i;
		}
	}

	return -1;
}
