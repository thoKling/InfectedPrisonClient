#pragma once

#include <SFML/Graphics.hpp>
#include <list>   

#include "Utils.h"

class Inventory;
class Item;


class InventoryView : public sf::Drawable, public sf::Transformable
{
public:
	InventoryView(Inventory* inventory);
	~InventoryView();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleInputs(const sf::Event& event);

	void update();

private:
	Inventory* _inventory;

	//Dans chaque carré de 64/64 se trouve potentiellement un item. Tableau selon [y,x]
	std::vector<std::vector<Item*>> _itemOnScreen;


	// base de l'inventaire
	float _baseWidth = WINDOWS_WIDTH / 2 - 2 * 64;
	float _baseHeight = WINDOWS_HEIGHT - WINDOWS_HEIGHT / 4;
	float _baseTop = WINDOWS_HEIGHT / 8;
	float _baseLeft = WINDOWS_WIDTH / 4 + 2* 64;
};

