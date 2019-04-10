#pragma once

#include <SFML/Graphics.hpp>

#include "Inventory.h";


class InventoryView : public sf::Drawable, public sf::Transformable
{
public:
	InventoryView(Inventory* inventory);
	~InventoryView();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(Inventory* inventory);

private:
	Inventory* _inventory;

	std::list<Item*> _items;
};

