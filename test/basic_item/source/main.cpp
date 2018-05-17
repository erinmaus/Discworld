#include <iostream>
#include "twoflower/brochure.hpp"
#include "mapp/game/game.hpp"
#include "mapp/game/item.hpp"
#include "mapp/game/shop.hpp"

int main()
{
	twoflower::Brochure brochure;
	mapp::Game game(brochure);

	mapp::ItemDefinition item_definition;
	item_definition.name = "Amulet of Yendor";
	auto item = game.add(item_definition);

	mapp::ShopDefinition shop_definition;
	shop_definition.name = "Amulet Shoppe";
	auto shop = game.add(shop_definition);
	game.add(shop, item, 10);

	auto resources = brochure.resources();
	for (auto i = resources.begin(); i != resources.end(); ++i)
	{
		std::cout << "name: " << i->get_name() << ", id: " << i->get_id() << std::endl;

		auto actions = brochure.actions(*i);
		for (auto j = actions.begin(); j != actions.end(); ++j)
		{
			std::cout << " - " << j->get_type().name << std::endl;
			auto requirements = brochure.requirements(*j);
			for (auto k = requirements.begin(); k != requirements.end(); ++k)
			{
				std::string result;
				if (k->is_input())
				{
					result = "input";
				}
				else if (k->is_output())
				{
					result = "output";
				}
				else
				{
					result = "req";
				}

				std::cout << "  - (" << result << ") " << (int)k->get_count() << ", " << k->get_resource().get_name() << std::endl;
			}
		}
	}

	std::cout << "inventory:" << std::endl;
	auto inventory = game.inventory(shop);
	for (auto item: inventory)
	{
		std::cout << " - " << item.resource.get_name() << std::endl;
	}

	return 0;
}
