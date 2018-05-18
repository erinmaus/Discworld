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
		explicit Brochure(const std::string& filename = "");
		~Brochure();

		ActionDefinition create_action_definition(const std::string& name);
		bool try_get_action_definition(
			const ID& id,
			ActionDefinition& result) const;

		struct ActionDefinitionIterator;
		ActionDefinitionIterator action_definitions_begin() const;
		ActionDefinitionIterator action_definitions_end() const;

		void create();

	private:
		class Database;
		class Statement;
		class Table;

		std::shared_ptr<Database> database;
	};

	struct Brochure::ActionDefinitionIterator :
		public std::iterator<
			std::input_iterator_tag,
			ActionDefinition,
			std::size_t,
			const ActionDefinition*,
			const ActionDefinition&>
	{
	public:
		friend class Brochure;

		ActionDefinitionIterator() = default;
		~ActionDefinitionIterator();

		ActionDefinitionIterator& operator ++();
		ActionDefinitionIterator operator ++(int);
		bool operator ==(const ActionDefinitionIterator& other) const;
		bool operator !=(const ActionDefinitionIterator& other) const;

		pointer operator ->() const;
		value_type operator *() const;

	private:
		explicit ActionDefinitionIterator(
			const Brochure& brochure,
			Statement& statement);
		void next();

		const Brochure* brochure = nullptr;
		std::shared_ptr<Statement> statement;
		bool end = true;
		ActionDefinition value;
	};
}

#endif
