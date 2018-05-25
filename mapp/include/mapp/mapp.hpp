// MAPP
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef MAPP_HPP
#define MAPP_HPP

#ifdef MAPP_BUILDING_WINDOWS
	#define MAPP_EXPORT __declspec(dllexport)
#else
	#define MAPP_EXPORT
#endif

#include "twoflower/meta/recordValue.hpp"

extern "C"
{
	#include "lua.h"
}

void mapp_record_value_to_lua(lua_State* L, const twoflower::RecordValue& value);
bool mapp_record_value_from_lua(
	lua_State* L,
	twoflower::RecordValue& result,
	int index);

#endif
