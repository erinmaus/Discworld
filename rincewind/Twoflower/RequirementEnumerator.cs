// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using System.Collections;
using System.Collections.Generic;

namespace Dormouse.Rincewind.Twoflower
{
	public class RequirementEnumerator : IEnumerator<Requirement>
	{
		IntPtr mIterator, mEndIterator;

		Requirement mCurrent;
		public Requirement Current
		{
			get { return mCurrent; }
		}

		object IEnumerator.Current
		{
			get { return mCurrent; }
		}

		public RequirementEnumerator(IntPtr begin, IntPtr end)
		{
			mIterator = begin;
			mEndIterator = end;
		}

		~RequirementEnumerator()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (mIterator != IntPtr.Zero)
			{
				Glooper.twoflower_free_requirements_iterator(mIterator);
				mIterator = IntPtr.Zero;
			}

			if (mEndIterator != IntPtr.Zero)
			{
				Glooper.twoflower_free_requirements_iterator(mEndIterator);
				mEndIterator = IntPtr.Zero;
			}

			GC.SuppressFinalize(this);
		}

		public bool MoveNext()
		{
			if (mIterator == IntPtr.Zero || mEndIterator == IntPtr.Zero)
			{
				return false;
			}

			if (!Glooper.twoflower_requirements_iterator_equals(mIterator, mEndIterator))
			{
				mCurrent = new Requirement(Glooper.twoflower_requirements_iterator_get_value(mIterator), true);
				Glooper.twoflower_requirements_iterator_next(mIterator);
				return true;
			}

			Dispose();
			return false;
		}

		public void Reset()
		{
			throw new NotImplementedException();
		}
	}
}
