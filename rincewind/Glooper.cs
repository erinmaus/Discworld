// RINCEWIND
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

using System;
using System.Text;
using System.Runtime.InteropServices;

using size_t = System.IntPtr;

namespace Dormouse.Rincewind
{
	public static class Glooper
	{
		// TODO: Cross platform.
#if RINCEWIND_DEBUG
		public const string GlooperSharedLib = "Glooper_debug.dll";
#else
		public const string GlooperSharedLib = "Glooper.dll";
#endif


		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_create_action();
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_action(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_action_get_id(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_action_get_type_id(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_action_get_type_name(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_action_get_is_getter(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_action_get_task(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern float twoflower_action_get_cost_multiplier(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_action_get_has_cost_multiplier(IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_id(IntPtr action, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_type_id(IntPtr action, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_type_name(IntPtr action, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_is_getter(IntPtr action, bool value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_task(IntPtr action, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_cost_multiplier(IntPtr action, float value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_action_set_has_cost_multiplier(IntPtr action, bool value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_create_resource();
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_resource(IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_resource_get_id(IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resource_get_name(IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_resource_get_type_id(IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resource_get_type_name(IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_resource_set_id(IntPtr resource, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_resource_set_name(IntPtr resource, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_resource_set_type_id(IntPtr resource, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_resource_set_type_name(IntPtr resource, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_create_requirement();
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_requirement(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_requirement_get_id(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_requirement_get_resource(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_requirement_get_action(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern float twoflower_requirement_get_count(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_requirement_get_is_input(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_requirement_get_is_output(IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_id(IntPtr requirement, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_resource(IntPtr requirement, IntPtr value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_action(IntPtr requirement, IntPtr value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_count(IntPtr requirement, float value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_is_input(IntPtr requirement, bool value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirement_set_is_output(IntPtr requirement, bool value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_create_brochure(string filename);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_brochure(IntPtr brochure);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_brochure_add_resource_type(IntPtr brochure, string name);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_remove_resource_type(IntPtr brochure, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_add_resource(IntPtr brochure, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_update_resource(IntPtr brochure, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_remove_resource(IntPtr brochure, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_resource_type_name(IntPtr brochure, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern size_t twoflower_brochure_get_resource_types_count(IntPtr brochure, string name);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern size_t twoflower_brochure_get_resource_types(IntPtr brochure, string name, int[] ids, size_t length);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_has_action_definition(IntPtr brochure, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_int(IntPtr brochure, IntPtr resource, string field, ref int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_float(IntPtr brochure, IntPtr resource, string field, ref float value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_string_length(IntPtr brochure, IntPtr resource, string field, ref IntPtr value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_string(IntPtr brochure, IntPtr resource, string field, StringBuilder value, size_t value_length);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_blob_length(IntPtr brochure, IntPtr resource, string field, ref IntPtr value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_get_userdata_blob(IntPtr brochure, IntPtr resource, string field, byte[] value, size_t value_length);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_has_userdata(IntPtr brochure, IntPtr resource, string field);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_set_userdata_int(IntPtr brochure, IntPtr resource, string field, int value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_set_userdata_float(IntPtr brochure, IntPtr resource, string field, float value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_set_userdata_string(IntPtr brochure, IntPtr resource, string field, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_set_userdata_blob(IntPtr brochure, IntPtr resource, string field, byte[] value, size_t value_length);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_unset_userdata(IntPtr brochure, IntPtr resource, string field);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern int twoflower_brochure_add_action_definition(IntPtr brochure, IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_update_action(IntPtr brochure, IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_remove_action(IntPtr brochure, IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_update_requirement(IntPtr brochure, IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_remove_requirement(IntPtr brochure, IntPtr requirement);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_connect_action(IntPtr brochure, IntPtr action, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_connect_requirement(IntPtr brochure, IntPtr requirement, IntPtr action, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_brochure_has_tag(IntPtr brochure, IntPtr resource, string value);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern size_t twoflower_brochure_get_num_tags(IntPtr brochure, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern size_t twoflower_brochure_get_tags(IntPtr brochure, IntPtr resource, IntPtr value, size_t value_length);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_add_tag(IntPtr brochure, IntPtr resource, string tag);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_brochure_remove_tag(IntPtr brochure, IntPtr resource, string tag);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_resource_from_action(IntPtr brochure, IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_resources(IntPtr brochure);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_resources(IntPtr resources);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_by_name(IntPtr resources, string name, int type);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_by_fuzzy_name(IntPtr resources, string name, int type);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_by_type(IntPtr resources, int type);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_begin(IntPtr resources);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_end(IntPtr resources);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_resources_has(IntPtr resources, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_get(IntPtr resources, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_resources_iterator_get_value(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_resources_iterator_next(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_resources_iterator_equals(IntPtr a, IntPtr b);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_resources_iterator(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_actions(IntPtr brochure);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_actions_for_resource(IntPtr brochure, IntPtr resource);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_actions(IntPtr actions);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_by_type(IntPtr actions, int type);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_by_name(IntPtr actions, string name, string type);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_getters(IntPtr actions);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_definitions(IntPtr actions);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_definitions_by_name(IntPtr actions, string name);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_begin(IntPtr actions);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_end(IntPtr actions);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_actions_has(IntPtr actions, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_get(IntPtr actions, int id);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_actions_iterator_get_value(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_actions_iterator_next(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_actions_iterator_equals(IntPtr a, IntPtr b);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_actions_iterator(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_brochure_get_requirements(IntPtr brochure, IntPtr action);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_requirements_begin(IntPtr requirements);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_requirements_end(IntPtr requirements);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_requirements(IntPtr requirements);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr twoflower_requirements_iterator_get_value(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_requirements_iterator_next(IntPtr iter);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool twoflower_requirements_iterator_equals(IntPtr a, IntPtr b);
		[DllImport(GlooperSharedLib, CallingConvention = CallingConvention.Cdecl)]
		public static extern void twoflower_free_requirements_iterator(IntPtr iter);
	}
}
