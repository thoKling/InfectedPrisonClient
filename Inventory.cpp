#include "Inventory.h"



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

bool Inventory::AddItem(Item* item)
{
	_items.emplace_back(item);
	return true;
}

void Inventory::dropItem(Item * item)
{
	_items.remove(item);
}

void Inventory::removeStack(Item* item, unsigned int amount)
{
	auto it = std::find(_items.begin(), _items.end(), item);
	if (it != _items.end())
		(*it)->removeStack(amount);
}

unsigned int Inventory::getAmmos(WeaponType weaponType)
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		if ((*it)->getAmmoType() == weaponType)
			return (*it)->getStack();
	}
	return 0;
}

void Inventory::setAmmos(WeaponType weaponType, unsigned int amount)
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		if ((*it)->getAmmoType() == weaponType)
			return (*it)->removeStack(amount);
	}
}
