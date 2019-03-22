#include "Item.h"

#include "Character.h"

Item::Item()
{
}


Item::~Item()
{
}

void Item::use(Character* charac)
{
}

void Item::reload()
{
}

void Item::update() {

}

bool Item::isReloading()
{
	return false;
}

std::string Item::getWeaponType()
{
	return "NaW"; // Not a Weapon
}
