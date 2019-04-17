#include "Inventory.h"
#include "InventoryView.h"



Inventory::Inventory():
	_inventoryView(new InventoryView(this)),
	_currentItem(nullptr),
	_backpackSize(36)
{
}


Inventory::~Inventory()
{
	/*
	delete _currentItem;
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		delete *it;
	}
	delete _inventoryView;*/
}

bool Inventory::AddItem(Item* item)
{
	if (_items.size() <= _backpackSize) {
		_items.emplace_back(item);
		return true;
	}
	return false;
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

Item* Inventory::getCurrentItem() const
{
	return _currentItem;
}
void Inventory::setCurrentItem(Item* item)
{
	_currentItem = item;
}

InventoryView* Inventory::getInventoryView() const
{
	return _inventoryView;
}
