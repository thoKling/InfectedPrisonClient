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

	void handleInputs(const sf::Event& event);

private:
	Inventory* _inventory;

	std::list<Item*> _items;
	//Dans chaque carré de 64/64 se trouve potentiellement un item
	std::vector<std::vector<Item*>> _itemOnScreen;

};

