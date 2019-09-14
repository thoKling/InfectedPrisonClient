#include "Item.h"

class Player;

std::map<ItemType, std::string> Item::ItemTypesStr = {
   {ItemType::undefined,"undefined"},{ItemType::Key,"Key"},{ItemType::Gun,"Gun"},{ItemType::Ammunition,"Ammo"}
};

Item::Item()
{
}

Item::~Item()
{
}

void Item::use(Player* player)
{
}

unsigned int Item::reload(unsigned int stack)
{
	return 0;
}

void Item::update() {

}

bool Item::isReloading()
{
	return false;
}

ItemType Item::getItemType()
{
	return ItemType::undefined;
}

ItemType Item::getAmmoType()
{
	return ItemType::undefined;
}

unsigned int Item::getAmmo()
{
	return 0;
}

unsigned int Item::getStack()
{
	return _stack;
}

void Item::setStack(unsigned int stack)
{
	_stack = stack;
}

void Item::addStack(unsigned int stack)
{
	_stack += stack;
}

void Item::removeStack(unsigned int stack)
{
	_stack -= stack;
	if (_stack < 0) 
		stack = 0;
}
