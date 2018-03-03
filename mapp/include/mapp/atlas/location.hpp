// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef MAPP_ATLAS_LOCATION_HPP
#define MAPP_ATLAS_LOCATION_HPP

#include <string>
#include <vector>
#include "twoflower/relationships/resource.hpp"

namespace mapp
{
	struct Location
	{
		twoflower::Resource resource;
		int anchorX,  anchorY;
		bool has_anchor = false;
	};

	struct LocationDefinition
	{
		std::string name;
		int anchorX, anchorY;
		bool has_anchor = false;

		LocationDefinition() = default;
		LocationDefinition(const Location& location);
		LocationDefinition operator =(const Location& location);
	};

	typedef std::vector<Location> Locations;
}

inline mapp::LocationDefinition::LocationDefinition(const Location& location)
{
	*this = location;
}

inline mapp::LocationDefinition mapp::LocationDefinition::operator =(const Location& location)
{
	name = location.resource.get_name();
	anchorX = location.anchorX;
	anchorY = location.anchorY;
	has_anchor = location.has_anchor;
	return *this;
}

#endif
