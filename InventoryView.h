#pragma once

#include <SFML/Graphics.hpp>
#include <list>   

class Inventory;
class Item;


class InventoryView : public sf::Drawable, public sf::Transformable
{
public:
	InventoryView(Inventory* inventory);
	~InventoryView();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Inventory* _inventory;

	std::list<Item*> _items;
};

