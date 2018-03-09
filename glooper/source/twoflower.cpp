// GLOOPER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <algorithm>
#include "twoflower/relationships/action.hpp"
#include "twoflower/relationships/resource.hpp"
#include "twoflower/relationships/requirement.hpp"
#include "twoflower/brochure.hpp"
#include "glooper/twoflower.hpp"

extern "C"
GLOOPER_API twoflower_action* twoflower_create_action()
{
	return (twoflower_action*)new twoflower::Action();
}

extern "C"
GLOOPER_API void twoflower_free_action(twoflower_action* action)
{
	delete (twoflower::Action*)action;
}

extern "C"
GLOOPER_API int twoflower_action_get_id(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->get_id();
}

extern "C"
GLOOPER_API int twoflower_action_get_type_id(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->get_type().id;
}

extern "C"
GLOOPER_API const char* twoflower_action_get_type_name(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->get_type().name.c_str();
}

extern "C"
GLOOPER_API bool twoflower_action_get_is_getter(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->is_getter();
}

extern "C"
GLOOPER_API const char* twoflower_action_get_task(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->get_task().c_str();
}

extern "C"
GLOOPER_API float twoflower_action_get_cost_multiplier(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->get_cost_multiplier();
}

extern "C"
GLOOPER_API bool twoflower_action_get_has_cost_multiplier(const twoflower_action* action)
{
	auto a = (const twoflower::Action*)action;
	return a->has_cost_multiplier();
}

extern "C"
GLOOPER_API void twoflower_action_set_id(twoflower_action* action, int value)
{
	auto a = (twoflower::Action*)action;
	return a->builder().set_id(value);
}

extern "C"
GLOOPER_API void twoflower_action_set_type_id(twoflower_action* action, int value)
{
	auto a = (twoflower::Action*)action;
	auto t = a->get_type();
	t.id = value;
	a->builder().set_type(t);
}

extern "C"
GLOOPER_API void twoflower_action_set_type_name(twoflower_action* action, const char* value)
{
	auto a = (twoflower::Action*)action;
	auto t = a->get_type();
	t.name = value;
	a->builder().set_type(t);
}

extern "C"
GLOOPER_API void twoflower_action_set_is_getter(twoflower_action* action, bool value)
{
	auto a = (twoflower::Action*)action;
	a->builder().set_is_getter(value);
}

extern "C"
GLOOPER_API void twoflower_action_set_task(twoflower_action* action, const char* value)
{
	auto a = (twoflower::Action*)action;
	a->builder().set_task(value);
}

extern "C"
GLOOPER_API void twoflower_action_set_cost_multiplier(twoflower_action* action, float value)
{
	auto a = (twoflower::Action*)action;
	a->builder().set_cost_multiplier(value);
}

extern "C"
GLOOPER_API void twoflower_action_set_has_cost_multiplier(twoflower_action* action, bool value)
{
	auto a = (twoflower::Action*)action;
	if (value)
	{
		a->builder().set_cost_multiplier(1.0f);
	}
	else
	{
		a->builder().unset_cost_multiplier();
	}
}

extern "C"
GLOOPER_API twoflower_resource* twoflower_create_resource()
{
	return (twoflower_resource*)new twoflower::Resource();
}

extern "C"
GLOOPER_API void twoflower_free_resource(twoflower_resource* resource)
{
	delete (twoflower::Resource*)resource;
}

extern "C"
GLOOPER_API int twoflower_resource_get_id(const twoflower_resource* resource)
{
	const twoflower::Resource* r = (const twoflower::Resource*)resource;
	return r->get_id();
}

extern "C"
GLOOPER_API const char* twoflower_resource_get_name(const twoflower_resource* resource)
{
	const twoflower::Resource* r = (const twoflower::Resource*)resource;
	return r->get_name().c_str();
}

extern "C"
GLOOPER_API int twoflower_resource_get_type_id(const twoflower_resource* resource)
{
	const twoflower::Resource* r = (const twoflower::Resource*)resource;
	return r->get_type().id;
}

extern "C"
GLOOPER_API const char* twoflower_resource_get_type_name(const twoflower_resource* resource)
{
	const twoflower::Resource* r = (const twoflower::Resource*)resource;
	return r->get_type().name.c_str();
}

extern "C"
GLOOPER_API void twoflower_resource_set_id(const twoflower_resource* resource, int value)
{
	twoflower::Resource* r = (twoflower::Resource*)resource;
	r->builder().set_id(value);
}

extern "C"
GLOOPER_API void twoflower_resource_set_name(const twoflower_resource* resource, const char* value)
{
	twoflower::Resource* r = (twoflower::Resource*)resource;
	r->builder().set_name(value);
}

extern "C"
GLOOPER_API void twoflower_resource_set_type_id(const twoflower_resource* resource, int value)
{
	twoflower::Resource* r = (twoflower::Resource*)resource;
	auto t = r->get_type();
	t.id = value;
	r->builder().set_type(t);
}

extern "C"
GLOOPER_API void twoflower_resource_set_type_name(const twoflower_resource* resource, const char* value)
{
	twoflower::Resource* r = (twoflower::Resource*)resource;
	auto t = r->get_type();
	t.name = value;
	r->builder().set_type(t);
}

extern "C"
GLOOPER_API twoflower_requirement* twoflower_create_requirement()
{
	return (twoflower_requirement*)new twoflower::Requirement();
}

extern "C"
GLOOPER_API void twoflower_free_requirement(twoflower_requirement* requirement)
{
	delete (twoflower::Requirement*)requirement;
}

extern "C"
GLOOPER_API int twoflower_requirement_get_id(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return r->get_id();
}

extern "C"
GLOOPER_API const twoflower_resource* twoflower_requirement_get_resource(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return (const twoflower_resource*)&r->get_resource();
}

extern "C"
GLOOPER_API const twoflower_action* twoflower_requirement_get_action(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return (const twoflower_action*)&r->get_action();
}

extern "C"
GLOOPER_API float twoflower_requirement_get_count(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return r->get_count();
}

extern "C"
GLOOPER_API bool twoflower_requirement_get_is_input(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return r->is_input();
}

extern "C"
GLOOPER_API bool twoflower_requirement_get_is_output(const twoflower_requirement* requirement)
{
	auto r = (const twoflower::Requirement*)requirement;
	return r->is_output();
}

extern "C"
GLOOPER_API void twoflower_requirement_set_id(const twoflower_requirement* requirement, int value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_id(value);
}

extern "C"
GLOOPER_API void twoflower_requirement_set_resource(const twoflower_requirement* requirement, const twoflower_resource* value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_resource(*((const twoflower::Resource*)value));
}

extern "C"
GLOOPER_API void twoflower_requirement_set_action(const twoflower_requirement* requirement, const twoflower_action* value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_action(*((const twoflower::Action*)value));
}

extern "C"
GLOOPER_API void twoflower_requirement_set_count(const twoflower_requirement* requirement, float value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_count(value);
}

extern "C"
GLOOPER_API void twoflower_requirement_set_is_input(const twoflower_requirement* requirement, bool value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_is_input(value);
}

extern "C"
GLOOPER_API void twoflower_requirement_set_is_output(const twoflower_requirement* requirement, bool value)
{
	auto r = (twoflower::Requirement*)requirement;
	r->builder().set_is_output(value);
}

extern "C"
GLOOPER_API twoflower_brochure* twoflower_create_brochure(const char* filename)
{
	twoflower::Brochure* result;
	if (filename != nullptr)
	{
		result = new twoflower::Brochure(filename);
	}
	else
	{
		result = new twoflower::Brochure();
	}

	return (twoflower_brochure*)result;
}

extern "C"
GLOOPER_API void twoflower_free_brochure(twoflower_brochure* brochure)
{
	delete (twoflower::Brochure*)brochure;
}

extern "C"
GLOOPER_API int twoflower_brochure_add_resource_type(twoflower_brochure* brochure, const char* name)
{
	auto b = (twoflower::Brochure*)brochure;
	auto result = b->builder().add_resource_type(name);
	return result.id;
}

extern "C"
GLOOPER_API void twoflower_brochure_remove_resource_type(twoflower_brochure* brochure, int id)
{
	auto b = (twoflower::Brochure*)brochure;
	twoflower::Resource::Type type;
	type.id = id;
	b->builder().remove_resource_type(type);
}

extern "C"
GLOOPER_API const char* twoflower_brochure_get_resource_type_name(const twoflower_brochure* brochure, int id)
{
	auto b = (const twoflower::Brochure*)brochure;

	static twoflower::Resource::Type type;
	type = b->get_resource_type(id);

	return type.name.c_str();
}

extern "C"
GLOOPER_API size_t twoflower_brochure_get_resource_types_count(const twoflower_brochure* brochure, const char* name)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = b->get_resource_types(name);
	return r.size();
}

extern "C"
GLOOPER_API size_t twoflower_brochure_get_resource_types(const twoflower_brochure* brochure, const char* name, int* ids, size_t length)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = b->get_resource_types(name);
	for (size_t i = 0; i < r.size() && i < length; ++i)
	{
		ids[i] = r[i].id;
	}

	return std::min(r.size(), length);
}

extern "C"
GLOOPER_API bool twoflower_brochure_has_action_definition(const twoflower_brochure* brochure, int id)
{
	auto b = (const twoflower::Brochure*)brochure;
	return b->has_action_definition(id);
}

extern "C"
GLOOPER_API twoflower_resource* twoflower_brochure_add_resource(twoflower_brochure* brochure, const twoflower_resource* resource)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	auto result = new twoflower::Resource(b->builder().add_resource(*r));
	return (twoflower_resource*)result;
}

extern "C"
GLOOPER_API void twoflower_brochure_update_resource(twoflower_brochure* brochure, const twoflower_resource* resource)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().update_resource(*r);
}

extern "C"
GLOOPER_API void twoflower_brochure_remove_resource(twoflower_brochure* brochure, const twoflower_resource* resource)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().remove_resource(*r);
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_int(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, int* value)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	return b->get_userdata(*r, field, *value);
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_float(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, float* value)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	return b->get_userdata(*r, field, *value);
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_string_length(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, size_t* value)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;

	std::string v;
	if(b->get_userdata(*r, field, v))
	{
		*value = v.size();
		return true;
	}
	else
	{
		*value = 0;
		return false;
	}
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_string(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;

	std::string v;
	if(b->get_userdata(*r, field, v))
	{
		std::memcpy(value, v.data(), std::min(v.size(), value_length));
		return true;
	}
	else
	{
		return false;
	}
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_blob_length(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, size_t* value)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;

	std::vector<std::uint8_t> v;
	if(b->get_userdata(*r, field, v))
	{
		*value = v.size();
		return true;
	}
	else
	{
		*value = 0;
		return false;
	}
}

extern "C"
GLOOPER_API bool twoflower_brochure_get_userdata_blob(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;

	std::vector<std::uint8_t> v;
	if(b->get_userdata(*r, field, v))
	{
		std::memcpy(value, v.data(), std::min(v.size(), value_length));
		return true;
	}
	else
	{
		return false;
	}
}

extern "C"
GLOOPER_API bool twoflower_brochure_has_userdata(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* field)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	return b->has_userdata(*r, field);
}

extern "C"
GLOOPER_API void twoflower_brochure_set_userdata_int(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, int value)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().set_userdata(*r, field, value);
}

extern "C"
GLOOPER_API void twoflower_brochure_set_userdata_float(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, float value)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().set_userdata(*r, field, value);
}

extern "C"
GLOOPER_API void twoflower_brochure_set_userdata_string(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, const char* value)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().set_userdata(*r, field, std::string(value));
}

extern "C"
GLOOPER_API void twoflower_brochure_set_userdata_blob(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field, char* value, size_t value_length)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	std::vector<std::uint8_t> v(value, value + value_length);
	b->builder().set_userdata(*r, field, v);
}

extern "C"
GLOOPER_API void twoflower_brochure_unset_userdata(twoflower_brochure* brochure, const twoflower_resource* resource, const char* field)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().unset_userdata(*r, field);
}

extern "C"
GLOOPER_API int twoflower_brochure_add_action_definition(twoflower_brochure* brochure, const twoflower_action* action)
{
	auto b = (twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	auto result = b->builder().add_action_definition(*a);
	return result.id;
}

extern "C"
GLOOPER_API void twoflower_brochure_update_action(twoflower_brochure* brochure, const twoflower_action* action)
{
	auto b = (twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	b->builder().update_action(*a);
}

extern "C"
GLOOPER_API void twoflower_brochure_remove_action(twoflower_brochure* brochure, const twoflower_action* action)
{
	auto b = (twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	b->builder().remove_action(*a);
}


extern "C"
GLOOPER_API void twoflower_brochure_update_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Requirement*)requirement;
	b->builder().update_requirement(*r);
}

extern "C"
GLOOPER_API void twoflower_brochure_remove_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Requirement*)requirement;
	b->builder().remove_requirement(*r);
}


extern "C"
GLOOPER_API twoflower_action* twoflower_brochure_connect_action(twoflower_brochure* brochure, const twoflower_action* action, const twoflower_resource* resource)
{
	auto b = (twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	auto r = (const twoflower::Resource*)resource;

	auto result = new twoflower::Action(b->builder().connect(*a, *r));
	return (twoflower_action*)result;
}

extern "C"
GLOOPER_API twoflower_requirement* twoflower_brochure_connect_requirement(twoflower_brochure* brochure, const twoflower_requirement* requirement, const twoflower_action* action, const twoflower_resource* resource)
{
	auto b = (twoflower::Brochure*)brochure;
	auto j = (const twoflower::Requirement*)requirement;
	auto a = (const twoflower::Action*)action;
	auto i = (const twoflower::Resource*)resource;

	auto result = new twoflower::Requirement(b->builder().connect(*j, *a, *i));
	return (twoflower_requirement*)result;
}


extern "C"
GLOOPER_API bool twoflower_brochure_has_tag(const twoflower_brochure* brochure, const twoflower_resource* resource, const char* value)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	return b->has_tag(*r, value);
}

extern "C"
GLOOPER_API size_t twoflower_brochure_get_num_tags(const twoflower_brochure* brochure, const twoflower_resource* resource)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	auto tags = b->tags(*r);
	return tags.size();
}

extern "C"
GLOOPER_API size_t twoflower_brochure_get_tags(const twoflower_brochure* brochure, const twoflower_resource* resource, const char** value, size_t value_length)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;

	static std::unordered_set<std::string> tags;
	tags = b->tags(*r);

	size_t count = 0;
	auto iter = tags.begin();
	for (std::size_t i = 0; i < value_length && iter != tags.end(); ++i, ++iter)
	{
		value[i] = iter->c_str();
		++count;
	}

	return std::min(value_length, count);
}

extern "C"
GLOOPER_API void twoflower_brochure_add_tag(twoflower_brochure* brochure, const twoflower_resource* resource, const char* tag)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().add_tag(*r, tag);
}

extern "C"
GLOOPER_API void twoflower_brochure_remove_tag(twoflower_brochure* brochure, const twoflower_resource* resource, const char* tag)
{
	auto b = (twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	b->builder().remove_tag(*r, tag);
}

extern "C"
GLOOPER_API twoflower_resource* twoflower_brochure_get_resource_from_action(const twoflower_brochure* brochure, const twoflower_action* action)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	auto result = new twoflower::Resource(b->resource(*a));
	return (twoflower_resource*)result;
}

extern "C"
GLOOPER_API twoflower_resources* twoflower_brochure_get_resources(const twoflower_brochure* brochure)
{
	auto b = (twoflower::Brochure*)brochure;
	auto result = new twoflower::Brochure::Resources(b->resources());
	return (twoflower_resources*)result;
}

extern "C"
GLOOPER_API void twoflower_free_resources(twoflower_resources* resources)
{
	delete (twoflower::Brochure::Resources*)resources;
}

extern "C"
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_name(const twoflower_resources* resources, const char* name, int type)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Brochure::Resources::const_iterator(r->by_name(name, type));
	return (twoflower_resources_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_fuzzy_name(const twoflower_resources* resources, const char* name, int type)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Brochure::Resources::const_iterator(r->by_fuzzy_name(name, type));
	return (twoflower_resources_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_resources_iterator* twoflower_resources_by_type(const twoflower_resources* resources, int type)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Brochure::Resources::const_iterator(r->by_type(type));
	return (twoflower_resources_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_resources_iterator* twoflower_resources_begin(const twoflower_resources* resources)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Brochure::Resources::const_iterator(r->begin());
	return (twoflower_resources_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_resources_iterator* twoflower_resources_end(const twoflower_resources* resources)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Brochure::Resources::const_iterator(r->end());
	return (twoflower_resources_iterator*)result;
}

extern "C"
GLOOPER_API bool twoflower_resources_has(const twoflower_resources* resources, int id)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	return r->has(id);
}

extern "C"
GLOOPER_API twoflower_resource* twoflower_resources_get(const twoflower_resources* resources, int id)
{
	auto r = (const twoflower::Brochure::Resources*)resources;
	auto result = new twoflower::Resource(r->get(id));
	return (twoflower_resource*)result;
}


extern "C"
GLOOPER_API twoflower_resource* twoflower_resources_iterator_get_value(const twoflower_resources_iterator* iter)
{
	auto i = (const twoflower::Brochure::Resources::const_iterator*)iter;
	auto result = new	twoflower::Resource(**i);
	return (twoflower_resource*)result;
}

extern "C"
GLOOPER_API void twoflower_resources_iterator_next(twoflower_resources_iterator* iter)
{
	auto i = (twoflower::Brochure::Resources::const_iterator*)iter;
	++(*i);
}

extern "C"
GLOOPER_API bool twoflower_resources_iterator_equals(const twoflower_resources_iterator* a, const twoflower_resources_iterator* b)
{
	auto i = (const twoflower::Brochure::Resources::const_iterator*)a;
	auto j = (const twoflower::Brochure::Resources::const_iterator*)b;
	return *i == *j;
}

extern "C"
GLOOPER_API void twoflower_free_resources_iterator(twoflower_resources_iterator* iter)
{
	delete (twoflower::Brochure::Resources::const_iterator*)iter;
}

extern "C"
GLOOPER_API twoflower_actions* twoflower_brochure_get_actions(twoflower_brochure* brochure)
{
	auto b = (twoflower::Brochure*)brochure;
	auto result = new twoflower::Brochure::Actions(b->actions());
	return (twoflower_actions*)result;
}

extern "C"
GLOOPER_API twoflower_actions* twoflower_brochure_get_actions_for_resource(const twoflower_brochure* brochure, const twoflower_resource* resource)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto r = (const twoflower::Resource*)resource;
	auto result = new twoflower::Brochure::Actions(b->actions(*r));
	return (twoflower_actions*)result;
}


extern "C"
GLOOPER_API void twoflower_free_actions(twoflower_actions* actions)
{
	auto a = (twoflower::Brochure::Actions*)actions;
	delete a;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_by_type(const twoflower_actions* actions, int type)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->by_type(type));
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_by_name(const twoflower_actions* actions, const char* name, const char* type)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	if (type != nullptr)
	{
		auto result = new twoflower::Brochure::Actions::const_iterator(a->by_name(type, name));
		return (twoflower_actions_iterator*)result;
	}
	else
	{
		auto result = new twoflower::Brochure::Actions::const_iterator(a->by_name(type));
		return (twoflower_actions_iterator*)result;
	}
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_getters(const twoflower_actions* actions)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->getters());
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_definitions(const twoflower_actions* actions)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->definitions());
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_definitions_by_name(const twoflower_actions* actions, const char* name)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->definitions(name));
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_begin(const twoflower_actions* actions)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->begin());
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_actions_iterator* twoflower_actions_end(const twoflower_actions* actions)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Brochure::Actions::const_iterator(a->end());
	return (twoflower_actions_iterator*)result;
}

extern "C"
GLOOPER_API bool twoflower_actions_has(const twoflower_actions* actions, int id)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	return a->has(id);
}

extern "C"
GLOOPER_API twoflower_action* twoflower_actions_get(const twoflower_actions* actions, int id)
{
	auto a = (const twoflower::Brochure::Actions*)actions;
	auto result = new twoflower::Action(a->get(id));
	return (twoflower_action*)result;
}

extern "C"
GLOOPER_API twoflower_action* twoflower_actions_iterator_get_value(const twoflower_actions_iterator* iter)
{
	auto i = (const twoflower::Brochure::Actions::const_iterator*)iter;
	auto result = new	twoflower::Action(**i);
	return (twoflower_action*)result;
}

extern "C"
GLOOPER_API void twoflower_actions_iterator_next(twoflower_actions_iterator* iter)
{
	auto i = (twoflower::Brochure::Actions::const_iterator*)iter;
	++(*i);
}

extern "C"
GLOOPER_API bool twoflower_actions_iterator_equals(const twoflower_actions_iterator* a, const twoflower_actions_iterator* b)
{
	auto i = (const twoflower::Brochure::Actions::const_iterator*)a;
	auto j = (const twoflower::Brochure::Actions::const_iterator*)b;
	return *i == *j;
}

extern "C"
GLOOPER_API void twoflower_free_actions_iterator(twoflower_actions_iterator* iter)
{
	delete (twoflower::Brochure::Actions::const_iterator*)iter;
}

extern "C"
GLOOPER_API twoflower_requirements* twoflower_brochure_get_requirements(const twoflower_brochure* brochure, const twoflower_action* action)
{
	auto b = (const twoflower::Brochure*)brochure;
	auto a = (const twoflower::Action*)action;
	auto result = new twoflower::Brochure::Requirements(b->requirements(*a));
	return (twoflower_requirements*)result;
}

extern "C"
GLOOPER_API twoflower_requirements_iterator* twoflower_requirements_begin(const twoflower_requirements* requirements)
{
	auto r = (const twoflower::Brochure::Requirements*)requirements;
	auto result = new twoflower::Brochure::Requirements::const_iterator(r->begin());
	return (twoflower_requirements_iterator*)result;
}

extern "C"
GLOOPER_API twoflower_requirements_iterator* twoflower_requirements_end(const twoflower_requirements* requirements)
{
	auto r = (const twoflower::Brochure::Requirements*)requirements;
	auto result = new twoflower::Brochure::Requirements::const_iterator(r->end());
	return (twoflower_requirements_iterator*)result;
}

extern "C"
GLOOPER_API void twoflower_free_requirements(twoflower_requirements* requirements)
{
	delete (twoflower::Brochure::Requirements*)requirements;
}
extern "C"
GLOOPER_API twoflower_requirement* twoflower_requirements_iterator_get_value(const twoflower_requirements_iterator* iter)
{
	auto i = (const twoflower::Brochure::Requirements::const_iterator*)iter;
	auto result = new	twoflower::Requirement(**i);
	return (twoflower_requirement*)result;
}

extern "C"
GLOOPER_API void twoflower_requirements_iterator_next(twoflower_requirements_iterator* iter)
{
	auto i = (twoflower::Brochure::Requirements::const_iterator*)iter;
	++(*i);
}

extern "C"
GLOOPER_API bool twoflower_requirements_iterator_equals(const twoflower_requirements_iterator* a, const twoflower_requirements_iterator* b)
{
	auto i = (const twoflower::Brochure::Requirements::const_iterator*)a;
	auto j = (const twoflower::Brochure::Requirements::const_iterator*)b;
	return *i == *j;
}

extern "C"
GLOOPER_API void twoflower_free_requirements_iterator(twoflower_requirements_iterator* iter)
{
	delete (twoflower::Brochure::Requirements::const_iterator*)iter;
}
