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
	public class ResourceActionEnumerator : IEnumerator<ResourceAction>
	{
		IntPtr mIterator, mEndIterator;

		ResourceAction mCurrent;
		public ResourceAction Current
		{
			get { return mCurrent; }
		}

		object IEnumerator.Current
		{
			get { return mCurrent; }
		}

		public ResourceActionEnumerator(IntPtr begin, IntPtr end)
		{
			mIterator = begin;
			mEndIterator = end;
		}

		~ResourceActionEnumerator()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (mIterator != IntPtr.Zero)
			{
				Glooper.twoflower_free_actions_iterator(mIterator);
				mIterator = IntPtr.Zero;
			}

			if (mEndIterator != IntPtr.Zero)
			{
				Glooper.twoflower_free_actions_iterator(mEndIterator);
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

			if (!Glooper.twoflower_actions_iterator_equals(mIterator, mEndIterator))
			{
				mCurrent = new ResourceAction(Glooper.twoflower_actions_iterator_get_value(mIterator), true);
				Glooper.twoflower_actions_iterator_next(mIterator);
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
