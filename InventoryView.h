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

	void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos);

	void update();

	void addItem(Item* newItem);
	void removeItem(Item* deletedItem);

	std::vector<Item*> getDroppedItems();

	void deleteDroppedItems();
private:
	Inventory* _inventory;

	//Dans chaque carré de 64/64 se trouve potentiellement un item. Tableau selon [y,x]
	std::vector<std::vector<Item*>> _itemOnScreen;

	Item* _selectedItem;
	sf::Vector2f _selectedItemLocation;

	//fond flou
	sf::RectangleShape _blur;
	//cellule de l'inventaire
	sf::RectangleShape _inventoryShape;

	bool _isDragging;

	std::vector<Item*> _droppedItems;


	// base de l'inventaire
	float _baseWidth = WINDOWS_WIDTH / 2 - 2 * 64;
	float _baseHeight = WINDOWS_HEIGHT - WINDOWS_HEIGHT / 4;
	float _baseTop = WINDOWS_HEIGHT / 8;
	float _baseLeft = WINDOWS_WIDTH / 4 + 2* 64;

	void drop();
	void moveItem(Item* item, int x, int y);

	//if the selected item is in the hand, it removes it
	void removeSelectedItemFromHand();
	//if the selected item is in the inventory, it removes it
	void removeSelectedItemFromInventory(Item* itemInHand);
};

