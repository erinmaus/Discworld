// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_BROCHURE_HPP
#define TWOFLOWER_BROCHURE_HPP

#include <memory>

namespace twoflower
{
	class Brochure
	{
	public:
		explicit Brochure(const std::string& filename = "");
		~Brochure();

	private:
		class Database;
		class Statement;
		class Table;

		std::shared_ptr<Database> database;
	};
}

#endif