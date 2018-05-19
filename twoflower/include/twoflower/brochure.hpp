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
#include "twoflower/relationships/actionDefinition.hpp"
#include "twoflower/relationships/action.hpp"

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

		Iterator<ActionDefinition> action_definitions_begin() const;
		Iterator<ActionDefinition> action_definitions_end() const;

		void create();

	private:
		class Database;
		class Statement;
		class Table;

		template <typename T>
		struct IteratorImpl
		{
			static bool next(Statement& statement, T& value);
		};

		template <>
		struct IteratorImpl<ActionDefinition>
		{
			static bool next(Statement& statement, ActionDefinition& value);
		};

		std::shared_ptr<Database> database;
	};

	template <typename T>
	struct Brochure::Iterator :
		public std::iterator<
			std::input_iterator_tag,
			T,
			std::size_t,
			const T*,
			const T&>
	{
	public:
		friend class Brochure;

		Iterator() = default;
		~Iterator();

		Iterator& operator ++();
		Iterator operator ++(int);
		bool operator ==(const Iterator& other) const;
		bool operator !=(const Iterator& other) const;

		pointer operator ->() const;
		value_type operator *() const;

	private:
		explicit Iterator(
			const Brochure& brochure,
			Statement& statement);
		void next();

		const Brochure* brochure = nullptr;
		std::shared_ptr<Statement> statement;
		bool end = true;
		T value;
	};
}

template <typename T>
twoflower::Brochure::Iterator<T>::Iterator(
	const Brochure& brochure, Statement& statement) :
		brochure(&brochure),
		statement(new Statement(statement)),
		end(false)
{
	next();
}

template <typename T>
twoflower::Brochure::Iterator<T>::~Iterator()
{
	// Nothing.
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
	return statement.get() == other.statement.get() || (end && other.end);
}

template <typename T>
bool twoflower::Brochure::Iterator<T>::operator !=(
	const Iterator& other) const
{
	return !(*this == other);
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
