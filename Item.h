#pragma once

#include "DrawableEntity.h"

class PlayerController;
class Player;

enum ItemType {
	undefined,
	Key,
	Gun,
	Ammunition
};

class Item : public DrawableEntity
{
public:
	Item();
	~Item();
	virtual void use(Player* player);
	// Renvoit le nomdre d'ammo utilisée, recharge du nombre demandé
	virtual unsigned int reload(unsigned int stack);
	virtual void update();

	virtual unsigned int getStack();
	virtual void setStack(unsigned int stack);
	virtual void addStack(unsigned int stack);
	virtual void removeStack(unsigned int stack);

	// Weapons
	virtual bool isReloading();
	virtual unsigned int getAmmo();
	virtual ItemType getItemType();
	virtual ItemType getAmmoType();
	// Nécessaire pour la sérialization
	virtual ItemType getType() = 0;

	static std::map<ItemType, std::string> ItemTypesStr;

protected:
	unsigned int _stack = 0;
};

