// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dormouse.Rincewind.Twoflower
{
	public class Brochure : IDisposable
	{
		IntPtr mBrochure;

		public bool IsDisposed
		{
			get { return mBrochure == IntPtr.Zero; }
		}

		public IntPtr Handle
		{
			get { return mBrochure; }
		}

		public Brochure(string filename)
		{
			mBrochure = Glooper.twoflower_create_brochure(filename);
		}

		public Resource AddResource(Resource resource)
		{
			var handle = Glooper.twoflower_brochure_add_resource(mBrochure, resource.Handle);
			return new Resource(handle, true);
		}

		public void Remove(Resource resource)
		{
			Glooper.twoflower_brochure_remove_resource(mBrochure, resource.Handle);
		}

		public void Remove(ResourceAction action)
		{
			Glooper.twoflower_brochure_remove_action(mBrochure, action.Handle);
		}

		public void Remove(Requirement requirement)
		{
			Glooper.twoflower_brochure_remove_requirement(mBrochure, requirement.Handle);
		}

		public int AddResourceType(string name)
		{
			return Glooper.twoflower_brochure_add_resource_type(mBrochure, name);
		}

		public int[] GetResourceTypes(string name)
		{
			var count = Glooper.twoflower_brochure_get_resource_types_count(mBrochure, name).ToInt64();
			int[] result = new int[count];
			Glooper.twoflower_brochure_get_resource_types(mBrochure, name, result, new IntPtr(count));
			return result;
		}

		public string GetResourceTypeName(int id)
		{
			return System.Runtime.InteropServices.Marshal.PtrToStringAnsi(Glooper.twoflower_brochure_get_resource_type_name(mBrochure, id));
		}

		public int AddActionDefinition(ResourceAction action)
		{
			return Glooper.twoflower_brochure_add_action_definition(mBrochure, action.Handle);
		}

		public void RemoveActionDefinition(int id)
		{
			using (ResourceAction actionDefinition = new ResourceAction())
			{
				actionDefinition.TypeID = id;
				Glooper.twoflower_brochure_remove_action(mBrochure, actionDefinition.Handle);
			}
		}

		public bool HasActionDefinition(int id)
		{
			return Glooper.twoflower_brochure_has_action_definition(mBrochure, id);
		}

		public ResourceAction Connect(ResourceAction action, Resource resource)
		{
			var result = Glooper.twoflower_brochure_connect_action(mBrochure, action.Handle, resource.Handle);
			return new ResourceAction(result, true);
		}

		public Requirement Connect(Requirement requirement, ResourceAction action, Resource resource)
		{
			var result = Glooper.twoflower_brochure_connect_requirement(mBrochure, requirement.Handle, action.Handle, resource.Handle);
			return new Requirement(result, true);
		}

		public void Update(Resource resource)
		{
			Glooper.twoflower_brochure_update_resource(mBrochure, resource.Handle);
		}

		public void Update(ResourceAction action)
		{
			Glooper.twoflower_brochure_update_action(mBrochure, action.Handle);
		}

		public void Update(Requirement requirement)
		{
			Glooper.twoflower_brochure_update_requirement(mBrochure, requirement.Handle);
		}

		public void Dispose()
		{
			if (!IsDisposed)
			{
				Glooper.twoflower_free_brochure(mBrochure);
				mBrochure = IntPtr.Zero;

				GC.SuppressFinalize(this);
			}
		}
	}
}
