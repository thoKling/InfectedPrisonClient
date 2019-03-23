#pragma once

#include "Item.h"

class Ammo : public Item
{
public:
	Ammo(WeaponType ammoType);
	~Ammo();
	virtual WeaponType getAmmoType();

private:
	WeaponType _ammoType;
};

