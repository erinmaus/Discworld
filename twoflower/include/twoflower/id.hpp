// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_ID_HPP
#define TWOFLOWER_ID_HPP

namespace twoflower
{
	struct ID
	{
	public:
		ID();
		ID(const ID& other) = default;
		ID(ID&& other);
		ID(int value);
		~ID() = default;

		operator int() const;

		bool operator <(const ID& other);
		bool operator >(const ID& other);
		bool operator <=(const ID& other);
		bool operator >=(const ID& other);
		bool operator ==(const ID& other);
		bool operator !=(const ID& other);

		ID& operator =(int id);
		ID& operator =(const ID& other) = default;
		ID& operator =(ID&& other);

		static const ID NIL;

	private:
		int id = 0;
	};
}

#endif
