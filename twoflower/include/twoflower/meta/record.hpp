// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_META_RECORD_HPP
#define TWOFLOWER_META_RECORD_HPP

#include <vector>
#include "twoflower/meta/recordDefinition.hpp"
#include "twoflower/meta/recordValue.hpp"

namespace twoflower
{
	class Record
	{
	public:
		// The RecordDefinition must not have a shorter lifespan than the
		// Record.
		explicit Record(const RecordDefinition& definition);

		bool get(const std::string& column, RecordValue& result) const;
		bool get(std::size_t index, RecordValue& result) const;

		template <typename T>
		bool get(const std::string& column, T& result) const;

		template <typename T>
		bool get(std::size_t index, T& result) const;

		bool set(const std::string& column, const RecordValue& value);
		bool set(std::size_t index, const RecordValue& value);

		template <typename T>
		bool set(const std::string& column, const T& result);

		template <typename T>
		bool set(std::size_t index, const T& result);

	private:
		const RecordDefinition* definition;
		std::vector<RecordValue> values;
	};
}

template <typename T>
bool twoflower::Record::get(const std::string& column, T& result) const
{
	RecordValue value;
	if (get(column, value))
	{
		return value.get(result);
	}

	return false;
}

template <typename T>
bool twoflower::Record::get(std::size_t index, T& result) const
{
	RecordValue value;
	if (get(index, value))
	{
		return value.get(result);
	}

	return false;
}

template <typename T>
bool twoflower::Record::set(const std::string& column, const T& value)
{
	RecordValue v;
	v.set(value);

	return set(column, v);
}

template <typename T>
bool twoflower::Record::set(std::size_t index, const T& value)
{
	RecordValue v;
	v.set(value);

	return set(index, v);
}

#endif
