// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_RECORD_HPP
#define TWOFLOWER_RECORD_HPP

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

		bool set(const std::string& column, const RecordValue& value);
		bool set(std::size_t index, const RecordValue& value);

	private:
		const RecordDefinition* definition;
		std::vector<RecordValue> values;
	};
}

#endif
