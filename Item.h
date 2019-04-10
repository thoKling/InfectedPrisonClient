#pragma once

#include "DrawableEntity.h"

class PlayerController;
class Player;

enum WeaponType {
	NaW, // Not a Weapon
	Gun,
};

const std::string WeaponTypesStr[] = { "NaW", "Gun" };

class Item : public DrawableEntity
{
public:
	Item();
	~Item();
	virtual void use(Player* player);
	// Renvoit le nomdre d'ammo utilis�e, recharge du nombre demand�
	virtual unsigned int reload(unsigned int stack);
	virtual void update();

	virtual unsigned int getStack();
	virtual void setStack(unsigned int stack);
	virtual void addStack(unsigned int stack);
	virtual void removeStack(unsigned int stack);

	// Weapons
	virtual bool isReloading();
	virtual unsigned int getAmmo();
	virtual WeaponType getWeaponType();
	// Ammos
	virtual WeaponType getAmmoType();

protected:
	unsigned int _stack = 0;
};

