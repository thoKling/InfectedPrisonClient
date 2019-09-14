#include "Inventory.h"
#include "InventoryView.h"

#include <iostream>


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
		_inventoryView->addItem(item);
		std::cout << "capacity: " << _backpackSize - _items.size() << std::endl;
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
		if ((*it)->getStack() <= 0){
			_inventoryView->removeItem(*it);
			// note: the object my not be deleted because of vector::erase behaviour
			_items.erase(std::remove(_items.begin(), _items.end(), *it), _items.end());
		}
	}
}

unsigned int Inventory::getAmmos(ItemType weaponType)
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		if ((*it)->getAmmoType() == weaponType)
			return (*it)->getStack();
	}
	return 0;
}

void Inventory::setAmmos(ItemType weaponType, unsigned int amount)
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

std::vector<Item*> Inventory::getDroppedItems() {
	return _inventoryView->getDroppedItems();
}

void Inventory::deleteDroppedItems() {
	_inventoryView->deleteDroppedItems();
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
