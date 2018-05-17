// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <cassert>
#include <stdexcept>
#include "twoflower/brochure.hpp"
#include "brochure/detail/database.hpp"
#include "brochure/detail/statement.hpp"
#include "brochure/detail/table.hpp"

twoflower::Brochure::Brochure(const std::string& filename)
{
	database = std::make_shared<Database>(filename);
}

twoflower::Brochure::~Brochure()
{
	// Nothing.
}
