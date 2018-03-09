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
	public class ResourceAction : IDisposable
	{
		IntPtr mAction;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mAction; }
		}

		public bool IsDisposed
		{
			get { return mAction == IntPtr.Zero; }
		}

		public int ID
		{
			get { return Glooper.twoflower_action_get_id(mAction); }
			set { Glooper.twoflower_action_set_id(mAction, value); }
		}

		public bool IsGetter
		{
			get { return Glooper.twoflower_action_get_is_getter(mAction); }
			set { Glooper.twoflower_action_set_is_getter(mAction, value); }
		}

		public float? CostMultiplier
		{
			get
			{
				if (!Glooper.twoflower_action_get_has_cost_multiplier(mAction))
				{
					return null;
				}
				else
				{
					return Glooper.twoflower_action_get_cost_multiplier(mAction);
				}
			}
			set
			{
				if (!value.HasValue)
				{
					Glooper.twoflower_action_set_has_cost_multiplier(mAction, false);
				}
				else
				{
					Glooper.twoflower_action_set_cost_multiplier(mAction, value.Value);
				}
			}
		}

		public int TypeID
		{
			get { return Glooper.twoflower_action_get_type_id(mAction); }
			set { Glooper.twoflower_action_set_type_id(mAction, value); }
		}

		public string TypeName
		{
			get { return Marshal.PtrToStringAnsi(Glooper.twoflower_action_get_type_name(mAction)); }
			set { Glooper.twoflower_action_set_type_name(mAction, value); }
		}

		public ResourceAction()
		{
			mAction = Glooper.twoflower_create_action();
			mIsManaged = true;
		}

		public ResourceAction(IntPtr action, bool isManaged = false)
		{
			mAction = action;
			mIsManaged = isManaged;
		}

		~ResourceAction()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_action(mAction);
				mAction = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
