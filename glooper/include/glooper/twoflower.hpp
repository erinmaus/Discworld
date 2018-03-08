// GLOOPER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef GLOOPER_TWOFLOWER_HPP
#define GLOOPER_TWOFLOWER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// TODO: handle cross-platform stuff.
#ifndef GLOOPER_API
#ifdef GLOOPER_BUILDING_DLL
	#define GLOOPER_API __declspec(dllexport)
#else
	#define GLOOPER_API __declspec(dllimport)
#endif
#endif

typedef struct twoflower_action twoflower_action;
typedef struct twoflower_requirement twoflower_requirement;
typedef struct twoflower_resource twoflower_resource;
typedef struct twoflower_resources twoflower_resources;
typedef struct twoflower_resources_iterator twoflower_resources_iterator;
typedef struct twoflower_actions twoflower_actions;
typedef struct twoflower_brochure twoflower_brochure;
typedef struct twoflower_actions_iterator twoflower_actions_iterator;
typedef struct twoflower_requirements twoflower_requirements;
typedef struct twoflower_requirements_iterator twoflower_requirements_iterator;

GLOOPER_API twoflower_action* twoflower_create_action();
GLOOPER_API void twoflower_free_action(twoflower_action* action);
GLOOPER_API int twoflower_action_get_id(const twoflower_action* action);
GLOOPER_API int twoflower_action_get_type_id(const twoflower_action* action);
GLOOPER_API const char* twoflower_action_get_type_name(const twoflower_action* action);
GLOOPER_API bool twoflower_action_get_is_getter(const twoflower_action* action);
GLOOPER_API const char* twoflower_action_get_task(const twoflower_action* action);
GLOOPER_API float twoflower_action_get_cost_multiplier(const twoflower_action* action);
GLOOPER_API bool twoflower_action_get_has_cost_multiplier(const twoflower_action* action);
GLOOPER_API void twoflower_action_set_id(twoflower_action* action, int value);
GLOOPER_API void twoflower_action_set_type_id(twoflower_action* action, int value);
GLOOPER_API void twoflower_action_set_type_name(twoflower_action* action, const char* value);
GLOOPER_API void twoflower_action_set_is_getter(twoflower_action* action, bool value);
GLOOPER_API void twoflower_action_set_task(twoflower_action* action, const char* value);
GLOOPER_API void twoflower_action_set_cost_multiplier(twoflower_action* action, float value);
GLOOPER_API void twoflower_action_set_has_cost_multiplier(twoflower_action* action, bool value);

GLOOPER_API twoflower_resource* twoflower_create_resource();
GLOOPER_API void twoflower_free_resource(twoflower_resource* resource);
GLOOPER_API int twoflower_resource_get_id(const twoflower_resource* resource);
GLOOPER_API const char* twoflower_resource_get_name(const twoflower_resource* resource);
GLOOPER_API int twoflower_resource_get_type_id(const twoflower_resource* resource);
GLOOPER_API const char* twoflower_resource_get_type_name(const twoflower_resource* resource);
GLOOPER_API void twoflower_resource_set_id(const twoflower_resource* resource, int value);
GLOOPER_API void twoflower_resource_set_name(const twoflower_resource* resource, const char* value);
GLOOPER_API void twoflower_resource_set_type_id(const twoflower_resource* resource, int value);
GLOOPER_API void twoflower_resource_set_type_name(const twoflower_resource* resource, const char* value);

GLOOPER_API twoflower_requirement* twoflower_create_requirement();
GLOOPER_API void twoflower_free_requirement(twoflower_requirement* requirement);
GLOOPER_API int twoflower_requirement_get_id(const twoflower_requirement* requirement);
GLOOPER_API const twoflower_resource* twoflower_requirement_get_resource(const twoflower_requirement* requirement);
GLOOPER_API const twoflower_action* twoflower_requirement_get_action(const twoflower_requirement* requirement);
GLOOPER_API float twoflower_requirement_get_count(const twoflower_requirement* requirement);
GLOOPER_API bool twoflower_requirement_get_is_input(const twoflower_requirement* requirement);
GLOOPER_API bool twoflower_requirement_get_is_output(const twoflower_requirement* requirement);
GLOOPER_API void twoflower_requirement_set_id(const twoflower_requirement* requirement, int value);
GLOOPER_API void twoflower_requirement_set_resource(const twoflower_requirement* requirement, const twoflower_resource* value);
GLOOPER_API void twoflower_requirement_set_action(const twoflower_requirement* requirement, const twoflower_action* value);
GLOOPER_API void twoflower_requirement_set_count(const twoflower_requirement* requirement, float value);
GLOOPER_API void twoflower_requirement_set_is_input(const twoflower_requirement* requirement, bool value);
GLOOPER_API void twoflower_requirement_set_is_output(const twoflower_requirement* requirement, bool value);

GLOOPER_API twoflower_brochure* twoflower_create_brochure(const char* filename);
GLOOPER_API void twoflower_free_brochure(twoflower_brochure* brochure);
GLOOPER_API int twoflower_brochure_add_resource_type(twoflower_brochure* brochure, const char* name);
GLOOPER_API void twoflower_brochure_remove_resource_type(twoflower_brochure* brochure, int id);
GLOOPER_API const char* twoflower_brochure_get_resource_type_name(const twoflower_brochure* brochure, int id);
GLOOPER_API size_t twoflower_brochure_get_resource_types_count(const twoflower_brochure* brochure, const char* name);
GLOOPER_API size_t twoflower_brochure_get_resource_types(const twoflower_brochure* brochure, const char* name, int* ids, size_t length);
GLOOPER_API bool twoflower_brochure_has_action_definition(const twoflower_brochure* brochure, int id);
GLOOPER_API twoflower_resource* twoflower_brochure_add_resource(twoflower_brochure* brochure, const twoflower_resource* resource);
GLOOPER_API void twoflower_brochure_update_resource(twoflower_brochure* brochure, const twoflower_resource* resource);
GLOOPER_API void twoflower_brochure_remove_resource(twoflower_brochure* brochure, const twoflower_resource* resource);
GLOOPER_API bool twoflower_brochure_get_userdata_int(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, int* value);
GLOOPER_API bool twoflower_brochure_get_userdata_float(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, float* value);
GLOOPER_API bool twoflower_brochure_get_userdata_string_length(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, size_t* value);
GLOOPER_API bool twoflower_brochure_get_userdata_string(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length);
GLOOPER_API bool twoflower_brochure_get_userdata_blob_length(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, size_t* value);
GLOOPER_API bool twoflower_brochure_get_userdata_blob(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length);
GLOOPER_API bool twoflower_brochure_has_userdata(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field);
GLOOPER_API void twoflower_brochure_set_userdata_int(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, int value);
GLOOPER_API void twoflower_brochure_set_userdata_float(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, float value);
GLOOPER_API void twoflower_brochure_set_userdata_string(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, const char* value);
GLOOPER_API void twoflower_brochure_set_userdata_blob(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length);
GLOOPER_API void twoflower_brochure_unset_userdata(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field);
GLOOPER_API int twoflower_brochure_add_action_definition(twoflower_brochure* brochure, const twoflower_action* action);
GLOOPER_API void twoflower_brochure_update_action(twoflower_brochure* brochure, const twoflower_action* action);
GLOOPER_API void twoflower_brochure_remove_action(twoflower_brochure* brochure, const twoflower_action* action);
GLOOPER_API void twoflower_brochure_update_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement);
GLOOPER_API void twoflower_brochure_remove_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement);
GLOOPER_API twoflower_action* twoflower_brochure_connect_action(twoflower_brochure* brochure, const twoflower_action* action, const twoflower_resource* resource);
GLOOPER_API twoflower_requirement* twoflower_brochure_connect_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement, const twoflower_action* action, const twoflower_resource* resource);
GLOOPER_API bool twoflower_brochure_has_tag(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* value);
GLOOPER_API size_t twoflower_brochure_get_num_tags(const twoflower_brochure* brochure, const twoflower_resource* resource);
GLOOPER_API size_t twoflower_brochure_get_tags(const twoflower_brochure* brochure, const twoflower_resource* resource, const char** value, size_t value_length);
GLOOPER_API void twoflower_brochure_add_tag(twoflower_brochure* brochure, const twoflower_resource* resource, const char* tag);
GLOOPER_API void twoflower_brochure_remove_tag(twoflower_brochure* brochure, const twoflower_resource* resource, const char* tag);
GLOOPER_API twoflower_resource* twoflower_brochure_get_resource_from_action(const twoflower_brochure* brochure, const twoflower_action* action);
GLOOPER_API twoflower_resources* twoflower_brochure_get_resources(const twoflower_brochure* brochure);
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_name(const twoflower_resources* resources, const char* name, int type);
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_fuzzy_name(const twoflower_resources* resources, const char* name, int type);
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_type(const twoflower_resources* resources, int type);
GLOOPER_API twoflower_resources_iterator* twoflower_resources_begin(const twoflower_resources* resources);
GLOOPER_API twoflower_resources_iterator* twoflower_resources_end(const twoflower_resources* resources);
GLOOPER_API bool twoflower_resources_has(const twoflower_resources* resources, int id);
GLOOPER_API twoflower_resource* twoflower_resources_get(const twoflower_resources* resources, int id);
GLOOPER_API const twoflower_resources* twoflower_resources_iterator_get_value(const twoflower_resources_iterator* iter);
GLOOPER_API void twoflower_resources_iterator_next(twoflower_resources_iterator* iter);
GLOOPER_API bool twoflower_resources_iterator_equals(const twoflower_resources_iterator* a, const twoflower_resources_iterator* b);
GLOOPER_API void twoflower_free_resources_iterator(twoflower_resources_iterator* iter);
GLOOPER_API twoflower_actions* twoflower_brochure_get_actions(twoflower_brochure* brochure);
GLOOPER_API twoflower_actions* twoflower_brochure_get_actions_for_resource(const twoflower_brochure* brochure, const twoflower_resource* resource);
GLOOPER_API void twoflower_free_actions(twoflower_actions* actions);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_by_type(const twoflower_actions* actions, int type);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_by_name(const twoflower_actions* actions, const char* name, const char* type);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_getters(const twoflower_actions* actions);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_definitions(const twoflower_actions* actions);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_definitions_by_name(const twoflower_actions* actions, const char* name);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_begin(const twoflower_actions* actions);
GLOOPER_API twoflower_actions_iterator* twoflower_actions_end(const twoflower_actions* actions);
GLOOPER_API bool twoflower_actions_has(const twoflower_actions* actions, int id);
GLOOPER_API twoflower_action* twoflower_actions_get(const twoflower_actions* actions, int id);
GLOOPER_API const twoflower_action* twoflower_actions_iterator_get_value(const twoflower_actions_iterator* iter);
GLOOPER_API void twoflower_actions_iterator_next(twoflower_actions_iterator* iter);
GLOOPER_API bool twoflower_actions_iterator_equals(const twoflower_actions_iterator* a, const twoflower_actions_iterator* b);
GLOOPER_API void twoflower_free_actions_iterator(twoflower_actions_iterator* iter);
GLOOPER_API twoflower_requirements_iterator* twoflower_requirements_begin(const twoflower_requirements* requirements);
GLOOPER_API twoflower_requirements_iterator* twoflower_requirements_end(const twoflower_requirements* requirements);
GLOOPER_API void twoflower_free_requirements(twoflower_requirements* requirements);
GLOOPER_API const twoflower_requirement* twoflower_requirements_iterator_get_value(const twoflower_requirements_iterator* iter);
GLOOPER_API void twoflower_requirements_iterator_next(twoflower_requirements_iterator* iter);
GLOOPER_API bool twoflower_requirements_iterator_equals(const twoflower_requirements_iterator* a, const twoflower_requirements_iterator* b);
GLOOPER_API void twoflower_free_requirements_iterator(twoflower_requirements_iterator* iter);

#ifdef __cplusplus
}
#endif

#endif
