#pragma once

#include "Item.h"

class Ammo : public Item
{
public:
	Ammo(ItemType ammo);
	~Ammo();
	virtual ItemType getAmmoType();
	virtual ItemType getType();
private:
	ItemType _ammo;
};

