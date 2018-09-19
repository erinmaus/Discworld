// TWOFLOWER
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef TWOFLOWER_BROCHURE_HPP
#define TWOFLOWER_BROCHURE_HPP

#include <iterator>
#include <memory>
#include "twoflower/id.hpp"
#include "twoflower/meta/record.hpp"
#include "twoflower/meta/recordDefinition.hpp"
#include "twoflower/meta/query.hpp"
#include "twoflower/relationships/actionConstraint.hpp"
#include "twoflower/relationships/actionDefinition.hpp"
#include "twoflower/relationships/action.hpp"
#include "twoflower/relationships/resource.hpp"
#include "twoflower/relationships/resourceType.hpp"

namespace twoflower
{
	class Brochure
	{
	public:
		template <typename T>
		struct Iterator;

		explicit Brochure(const std::string& filename = "");
		~Brochure();

		ActionDefinition create_action_definition(const std::string& name);
		bool try_get_action_definition(
			const ID& id,
			ActionDefinition& result) const;
		bool try_get_action_definition(
			const std::string& name,
			ActionDefinition& result) const;

		Iterator<ActionDefinition> action_definitions_begin() const;
		Iterator<ActionDefinition> action_definitions_end() const;

		Action create_action(const ActionDefinition& action_definition);
		bool try_get_action(const ID& id, Action& result) const;
		ActionDefinition get_action_definition(const Action& action) const;

		Iterator<Action> actions_begin() const;
		Iterator<Action> actions_end() const;
		Iterator<Action> actions_by_definition(
			const ActionDefinition& action_definition) const;
		Iterator<Action> actions_by_resource(
			const Resource& resource) const;

		ResourceType create_resource_type(const std::string& name);
		bool try_get_resource_type(
			const ID& id,
			ResourceType& result) const;
		bool try_get_resource_type(
			const std::string& name,
			ResourceType& result) const;

		Iterator<ResourceType> resource_types_begin() const;
		Iterator<ResourceType> resource_types_end() const;

		Resource create_resource(
			const ResourceType& resource_type,
			const std::string& name,
			bool is_singleton);
		bool try_get_resource(const ID& id, Resource& result) const;
		ResourceType get_resource_type(const Resource& resource) const;

		Iterator<Resource> resources_begin() const;
		Iterator<Resource> resources_end() const;
		Iterator<Resource> resources_by_type(
			const ResourceType& resource_type) const;
		Iterator<Resource> resources_by_name(const std::string& name) const;
		Iterator<Resource> resources_by_name_and_type(
			const std::string& name,
			const ResourceType& resource_type) const;

		void connect(const Action& action, const Resource& resource);

		void connect(
			ActionConstraint::Type type,
			const Action& action,
			const Resource& resource,
			float quantity);

		Iterator<ActionConstraint> action_constraints_begin(
			ActionConstraint::Type type,
			const Action& action) const;
		Iterator<ActionConstraint> action_constraints_end() const;

		Action get_constraint_action(const ActionConstraint& constraint) const;
		Resource get_constraint_resource(const ActionConstraint& constraint) const;

		void create();
		void create(const RecordDefinition& definition);

		void insert(const RecordDefinition& definition, const Record& record);

		static const int UNLIMITED_POWER = -1;
		std::vector<Record> select(
			const RecordDefinition& definition,
			const Query& query,
			int limit = UNLIMITED_POWER) const;
		Record select_one(
			const RecordDefinition& definition,
			const Query& query) const;

	private:
		class Database;
		class Statement;
		class Table;

		static Statement* clone_statement(Statement* statement);
		static void delete_statement(Statement* statement);

		void statement_to_record(
			const Statement& statement,
			const RecordDefinition& definition,
			Record& result) const;

		static int record_definition_type_to_table_type(RecordDefinition::Type type);
		static std::string constraint_type_to_table_name(
			ActionConstraint::Type type);

		template <typename T>
		struct IteratorImpl
		{
			static bool next(Statement& statement, T& value);
		};

		std::shared_ptr<Database> database;
	};

	template <>
	struct Brochure::IteratorImpl<ActionDefinition>
	{
		static bool next(Statement& statement, ActionDefinition& value);
	};

	template <>
	struct Brochure::IteratorImpl<Action>
	{
		static bool next(Statement& statement, Action& value);
	};

	template <>
	struct Brochure::IteratorImpl<ResourceType>
	{
		static bool next(Statement& statement, ResourceType& value);
	};

	template <>
	struct Brochure::IteratorImpl<Resource>
	{
		static bool next(Statement& statement, Resource& value);
	};

	template <>
	struct Brochure::IteratorImpl<ActionConstraint>
	{
		static bool next(Statement& statement, ActionConstraint& value);
	};

	template <typename T>
	struct Brochure::Iterator
	{
	public:
		friend class Brochure;

		typedef std::input_iterator_tag iteratory_category;
		typedef std::size_t difference_type;
		typedef const T* pointer;
		typedef const T& value_type;

		Iterator() = default;
		Iterator(const Iterator& other);
		~Iterator();

		Iterator& operator ++();
		Iterator operator ++(int);
		bool operator ==(const Iterator& other) const;
		bool operator !=(const Iterator& other) const;

		Iterator& operator =(const Iterator& other);

		pointer operator ->() const;
		value_type operator *() const;

	private:
		explicit Iterator(
			const Brochure& brochure,
			Statement* statement);
		explicit Iterator(
			const Brochure& brochure,
			Statement* statement,
			const T& value);
		void next();

		const Brochure* brochure = nullptr;
		Statement* statement = nullptr;
		bool end = true;
		T value;
	};
}

template <typename T>
twoflower::Brochure::Iterator<T>::Iterator(
	const Brochure& brochure, Statement* statement) :
		brochure(&brochure),
		statement(statement),
		end(false)
{
	next();
}

template <typename T>
twoflower::Brochure::Iterator<T>::Iterator(const Iterator& other)
{
	*this = other;
}

template <typename T>
twoflower::Brochure::Iterator<T>::Iterator(
	const Brochure& brochure, Statement* statement, const T& value) :
		brochure(&brochure),
		statement(statement),
		end(false),
		value(value)
{
	next();
}

template <typename T>
twoflower::Brochure::Iterator<T>::~Iterator()
{
	if (statement)
	{
		Brochure::delete_statement(statement);
		statement = nullptr;
	}
}

template <typename T>
twoflower::Brochure::Iterator<T>&
twoflower::Brochure::Iterator<T>::operator ++()
{
	next();
	return *this;
}

template <typename T>
twoflower::Brochure::Iterator<T>
twoflower::Brochure::Iterator<T>::operator ++(int)
{
	next();
	return *this;
}

template <typename T>
bool twoflower::Brochure::Iterator<T>::operator ==(
	const Iterator& other) const
{
	return statement == other.statement || (end && other.end);
}

template <typename T>
bool twoflower::Brochure::Iterator<T>::operator !=(
	const Iterator& other) const
{
	return !(*this == other);
}

template <typename T>
twoflower::Brochure::Iterator<T>&
twoflower::Brochure::Iterator<T>::operator =(const Iterator& other)
{
	if (statement)
	{
		Brochure::delete_statement(statement);
	}

	brochure = other.brochure;
	statement = Brochure::clone_statement(other.statement);
	end = other.end;
	value = other.value;

	return *this;
}

template <typename T>
typename twoflower::Brochure::Iterator<T>::pointer
twoflower::Brochure::Iterator<T>::operator ->() const
{
	return &value;
}

template <typename T>
typename twoflower::Brochure::Iterator<T>::value_type
twoflower::Brochure::Iterator<T>::operator *() const
{
	return value;
}

template <typename T>
void twoflower::Brochure::Iterator<T>::next()
{
	if (end)
	{
		return;
	}
	
	if (!IteratorImpl<T>::next(*statement, value))
	{
		end = true;
	}
}

#endif
