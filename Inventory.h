#pragma once

#include <list>
#include "Item.h"


class Inventory
{
public:
	Inventory();
	~Inventory();

	// Renvoit vrai si on a pu le stocker, faux si on a plus de place (TODO)
	bool AddItem(Item* item);
	void dropItem(Item* item);
	void removeStack(Item* item, unsigned int amount);
	unsigned int getAmmos(WeaponType weaponType);
	void setAmmos(WeaponType weaponType, unsigned int amount);

	std::vector<Item*> getItems();

private:
	std::vector<Item*> _items;
};

