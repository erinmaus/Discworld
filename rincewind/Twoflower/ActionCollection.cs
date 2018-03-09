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
	public class ActionCollection : IDisposable
	{
		IntPtr mActions;
		bool mIsManaged;

		public IntPtr Handle
		{
			get { return mActions; }
		}

		public bool IsDisposed
		{
			get { return mActions == IntPtr.Zero; }
		}

		public ActionCollection(Brochure brochure)
		{
			mActions = Glooper.twoflower_brochure_get_actions(brochure.Handle);
			mIsManaged = true;
		}

		public ActionCollection(Brochure brochure, Resource resource)
		{
			mActions = Glooper.twoflower_brochure_get_actions_for_resource(brochure.Handle, resource.Handle);
			mIsManaged = true;
		}

		public ActionCollection(IntPtr handle, bool isManaged = false)
		{
			mActions = handle;
			mIsManaged = isManaged;
		}

		~ActionCollection()
		{
			Dispose();
		}

		class ActionQuery : IEnumerable<Action>
		{
			Func<IntPtr> mBegin;
			Func<IntPtr> mEnd;

			public ActionQuery(Func<IntPtr> begin, Func<IntPtr> end)
			{
				mBegin = begin;
				mEnd = end;
			}

			public IEnumerator<Action> GetEnumerator()
			{
				return new ActionEnumerator(mBegin(), mEnd());
			}

			IEnumerator IEnumerable.GetEnumerator()
			{
				return GetEnumerator();
			}
		}

		public IEnumerable<Action> Definitions()
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_definitions(mActions);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> Definitions(string name)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_definitions_by_name(mActions, name);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> Getters()
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_getters(mActions);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> ByType(int type)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_by_type(mActions, type);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> ByName(string name)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_by_name(mActions, name, null);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> ByName(string type, string name)
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_by_name(mActions, name, type);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public IEnumerable<Action> All()
		{
			Func<IntPtr> begin = () => Glooper.twoflower_actions_begin(mActions);
			Func<IntPtr> end = () => Glooper.twoflower_actions_end(mActions);
			return new ActionQuery(begin, end);
		}

		public bool Has(int id)
		{
			return Glooper.twoflower_actions_has(mActions, id);
		}

		public Action Get(int id)
		{
			return new Action(Glooper.twoflower_actions_get(mActions, id), true);
		}

		public void Dispose()
		{
			if (!IsDisposed && mIsManaged)
			{
				Glooper.twoflower_free_actions(mActions);
				mActions = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
