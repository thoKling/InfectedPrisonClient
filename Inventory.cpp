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
	_items.erase(std::remove(_items.begin(), _items.end(), item), _items.end());
}

void Inventory::removeStack(Item* item, unsigned int amount)
{
	auto it = std::find(_items.begin(), _items.end(), item);
	if (it != _items.end()) {
		(*it)->removeStack(amount);
		if ((*it)->getStack() <= 0)
			_items.erase(std::remove(_items.begin(), _items.end(), *it), _items.end());
	}
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
		if ((*it)->getAmmoType() == weaponType) {
			removeStack(*it, amount);
			break;
		}
	}
}

std::vector<Item*> Inventory::getItems() {
	return _items;
}
