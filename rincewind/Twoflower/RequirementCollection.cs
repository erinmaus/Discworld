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
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dormouse.Rincewind.Twoflower
{
	public class RequirementCollection : IDisposable
	{
		IntPtr mRequirements;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mRequirements; }
		}

		public bool IsDisposed
		{
			get { return mRequirements == IntPtr.Zero; }
		}

		public RequirementCollection(Brochure brochure, Action action)
		{
			mRequirements = Glooper.twoflower_brochure_get_requirements(brochure.Handle, action.Handle);
			mIsManaged = true;
		}

		public RequirementCollection(IntPtr handle, bool isManaged = false)
		{
			mRequirements = handle;
			mIsManaged = isManaged;
		}

		~RequirementCollection()
		{
			Dispose();
		}

		class RequirementQuery : IEnumerable<Requirement>
		{
			Func<IntPtr> mBegin;
			Func<IntPtr> mEnd;

			public RequirementQuery(Func<IntPtr> begin, Func<IntPtr> end)
			{
				mBegin = begin;
				mEnd = end;
			}

			public IEnumerator<Requirement> GetEnumerator()
			{
				return new RequirementEnumerator(mBegin(), mEnd());
			}

			IEnumerator IEnumerable.GetEnumerator()
			{
				return GetEnumerator();
			}
		}

		public IEnumerable<Requirement> All()
		{
			Func<IntPtr> begin = () => Glooper.twoflower_requirements_begin(mRequirements);
			Func<IntPtr> end = () => Glooper.twoflower_requirements_end(mRequirements);
			return new RequirementQuery(begin, end);
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_requirements(mRequirements);
				mRequirements = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
