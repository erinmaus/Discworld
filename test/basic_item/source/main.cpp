#include <iostream>
#include "twoflower/brochure.hpp"
#include "mapp/game/game.hpp"
#include "mapp/game/item.hpp"

int main()
{
	twoflower::Brochure brochure("sample.gamedb");
	mapp::Game game(brochure);

	mapp::ItemDefinition item;
	item.name = "Amulet of Yendor";
	game.add(item);

	auto resources = brochure.resources();
	for (auto i = resources.begin(); i != resources.end(); ++i)
	{
		std::cout << "name: " << i->get_name() << ", id: " << i->get_id() << std::endl;
	}

	return 0;
}
