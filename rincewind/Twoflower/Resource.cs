// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using System.Runtime.InteropServices;

namespace Dormouse.Rincewind.Twoflower
{
	public class Resource : IDisposable
	{
		IntPtr mResource;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mResource; }
		}

		public bool IsDisposed
		{
			get { return mResource == IntPtr.Zero; }
		}
		
		public int ID
		{
			get { return Glooper.twoflower_resource_get_id(mResource); }
			set { Glooper.twoflower_resource_set_id(mResource, value); }
		}

		public string Name
		{
			get { return Marshal.PtrToStringAnsi(Glooper.twoflower_resource_get_name(mResource)); }
			set { Glooper.twoflower_resource_set_name(mResource, value); }
		}

		public int TypeID
		{
			get { return Glooper.twoflower_resource_get_type_id(mResource); }
			set { Glooper.twoflower_resource_set_type_id(mResource, value); }
		}

		public string TypeName
		{
			get { return Marshal.PtrToStringAnsi(Glooper.twoflower_resource_get_type_name(mResource)); }
			set { Glooper.twoflower_resource_set_type_name(mResource, value); }
		}

		public Resource()
		{
			mResource = Glooper.twoflower_create_resource();
			mIsManaged = true;
		}

		public Resource(IntPtr resource, bool isManaged = false)
		{
			mResource = resource;
			mIsManaged = isManaged;
		}

		~Resource()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_resource(mResource);
				mResource = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
