#pragma once

#include <list>
#include "Item.h"

class InventoryView;

class Inventory
{
public:
	Inventory();
	~Inventory();

	// Renvoit vrai si on a pu le stocker, faux si on a plus de place (TODO)
	bool AddItem(Item* item);
	void dropItem(Item* item);
	void removeStack(Item* item, unsigned int amount);
	unsigned int getAmmos(ItemType weaponType);
	void setAmmos(ItemType weaponType, unsigned int amount);

	std::vector<Item*> getItems();
	std::vector<Item*> getDroppedItems();
	void deleteDroppedItems();

	Item* getCurrentItem() const;
	void setCurrentItem(Item* item);
	
	InventoryView* getInventoryView() const;

private:
	int _backpackSize;

	std::vector<Item*> _items;

	InventoryView* _inventoryView;

	Item* _currentItem;
};

