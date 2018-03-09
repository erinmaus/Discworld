// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;

namespace Dormouse.Rincewind.Twoflower
{
	public class Requirement : IDisposable
	{
		IntPtr mRequirement;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mRequirement; }
		}

		public bool IsDisposed
		{
			get { return mRequirement == IntPtr.Zero; }
		}

		public int ID
		{
			get { return Glooper.twoflower_requirement_get_id(mRequirement); }
			set { Glooper.twoflower_requirement_set_id(mRequirement, value); }
		}

		public bool IsInput
		{
			get { return Glooper.twoflower_requirement_get_is_input(mRequirement); }
			set { Glooper.twoflower_requirement_set_is_input(mRequirement, value); }
		}

		public bool IsOutput
		{
			get { return Glooper.twoflower_requirement_get_is_output(mRequirement); }
			set { Glooper.twoflower_requirement_set_is_output(mRequirement, value); }
		}

		public Resource Resource
		{
			get { return new Resource(Glooper.twoflower_requirement_get_resource(mRequirement)); }
			set { Glooper.twoflower_requirement_set_resource(mRequirement, value.Handle); }
		}

		public Action Action
		{
			get { return new Action(Glooper.twoflower_requirement_get_action(mRequirement)); }
			set { Glooper.twoflower_requirement_set_action(mRequirement, value.Handle); }
		}

		public float Count
		{
			get { return Glooper.twoflower_requirement_get_count(mRequirement); }
			set { Glooper.twoflower_requirement_set_count(mRequirement, value); }
		}

		public Requirement()
		{
			mRequirement = Glooper.twoflower_create_requirement();
			mIsManaged = true;
		}

		public Requirement(IntPtr requirement, bool isManaged = false)
		{
			mRequirement = requirement;
			mIsManaged = isManaged;
		}

		~Requirement()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_requirement(mRequirement);
				mRequirement = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
