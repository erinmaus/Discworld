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
	public class ResourceCollection : IDisposable
	{
		IntPtr mResources;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mResources; }
		}

		public bool IsDisposed
		{
			get { return mResources == IntPtr.Zero; }
		}

		public ResourceCollection(Brochure brochure)
		{
			mResources = Glooper.twoflower_brochure_get_resources(brochure.Handle);
			mIsManaged = true;
		}

		public ResourceCollection(IntPtr handle, bool isManaged = false)
		{
			mResources = handle;
			mIsManaged = isManaged;
		}

		~ResourceCollection()
		{
			Dispose();
		}

		class ResourceQuery : IEnumerable<Resource>
		{
			Func<IntPtr> mBegin;
			Func<IntPtr> mEnd;

			public ResourceQuery(Func<IntPtr> begin, Func<IntPtr> end)
			{
				mBegin = begin;
				mEnd = end;
			}

			public IEnumerator<Resource> GetEnumerator()
			{
				return new ResourceEnumerator(mBegin(), mEnd());
			}

			IEnumerator IEnumerable.GetEnumerator()
			{
				return GetEnumerator();
			}
		}

		public IEnumerable<Resource> ByType(int type)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_by_type(mResources, type);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public IEnumerable<Resource> ByName(string name)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_by_name(mResources, name, 0);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public IEnumerable<Resource> ByName(string name, int type)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_by_name(mResources, name, type);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public IEnumerable<Resource> ByFuzzyName(string name)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_by_name(mResources, name, 0);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public IEnumerable<Resource> ByFuzzyName(string name, int type)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_by_name(mResources, name, type);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public IEnumerable<Resource> All()
		{
			Func<IntPtr> begin = () => Glooper.twoflower_resources_begin(mResources);
			Func<IntPtr> end = () => Glooper.twoflower_resources_end(mResources);
			return new ResourceQuery(begin, end);
		}

		public bool Has(int id)
		{
			return Glooper.twoflower_resources_has(mResources, id);
		}

		public Resource Get(int id)
		{
			return new Resource(Glooper.twoflower_resources_get(mResources, id), true);
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_resources(mResources);
				mResources = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
