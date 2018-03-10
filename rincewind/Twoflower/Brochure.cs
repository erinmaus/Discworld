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
using System.Runtime.InteropServices;

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

		public int? GetUserdataInt32(Resource resource, string field)
		{
			unsafe
			{
				int value = 0;
				if (Glooper.twoflower_brochure_get_userdata_int(mBrochure, resource.Handle, field, ref value))
				{
					return value;
				}

				return null;
			}
		}

		public void SetUserdata(Resource resource, string field, int value)
		{
			Glooper.twoflower_brochure_set_userdata_int(mBrochure, resource.Handle, field, value);
		}

		public float? GetUserdataSingle(Resource resource, string field)
		{
			unsafe
			{
				float value = 0.0f;
				if (Glooper.twoflower_brochure_get_userdata_float(mBrochure, resource.Handle, field, ref value))
				{
					return value;
				}

				return null;
			}
		}

		public void SetUserdata(Resource resource, string field, float value)
		{
			Glooper.twoflower_brochure_set_userdata_float(mBrochure, resource.Handle, field, value);
		}

		public string GetUserdataString(Resource resource, string field)
		{
			IntPtr size = IntPtr.Zero;
			if (Glooper.twoflower_brochure_get_userdata_string_length(mBrochure, resource.Handle, field, ref size))
			{
				StringBuilder result = new StringBuilder(size.ToInt32());
				if (Glooper.twoflower_brochure_get_userdata_string(mBrochure, resource.Handle, field, result, size))
				{
					return result.ToString();
				}
			}

			return null;
		}

		public void SetUserdata(Resource resource, string field, string value)
		{
			Glooper.twoflower_brochure_set_userdata_string(mBrochure, resource.Handle, field, value);
		}

		public bool HasTag(Resource resource, string tag)
		{
			return Glooper.twoflower_brochure_has_tag(mBrochure, resource.Handle, tag);
		}

		public void AddTag(Resource resource, string tag)
		{
			Glooper.twoflower_brochure_add_tag(mBrochure, resource.Handle, tag);
		}

		public void RemoveTag(Resource resource, string tag)
		{
			Glooper.twoflower_brochure_remove_tag(mBrochure, resource.Handle, tag);
		}

		public string[] GetTags(Resource resource)
		{
			var count = Glooper.twoflower_brochure_get_num_tags(mBrochure, resource.Handle);

			IntPtr[] tags = new IntPtr[count.ToInt32()];
			Glooper.twoflower_brochure_get_tags(mBrochure, resource.Handle, tags, count);

			string[] result = new string[count.ToInt32()];
			for (int i = 0; i < tags.Length; ++i)
			{
				result[i] = Marshal.PtrToStringAnsi(tags[i]);
			}

			return result;
		}

		public byte[] GetUserdataBytes(Resource resource, string field)
		{
			IntPtr size = IntPtr.Zero;
			if (Glooper.twoflower_brochure_get_userdata_blob_length(mBrochure, resource.Handle, field, ref size))
			{
				byte[] result = new byte[size.ToInt64()];
				if (Glooper.twoflower_brochure_get_userdata_blob(mBrochure, resource.Handle, field, result, size))
				{
					return result;
				}
			}

			return null;
		}

		public void UnsetUserdata(Resource resource, string field)
		{
			Glooper.twoflower_brochure_unset_userdata(mBrochure, resource.Handle, field);
		}

		public bool HasUserdata(Resource resource, string field)
		{
			return Glooper.twoflower_brochure_has_userdata(mBrochure, resource.Handle, field);
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
