#pragma once

#include "DrawableEntity.h"

class Character;

class Item : public DrawableEntity
{
public:
	Item();
	~Item();
	virtual void use(Character* charac);
	virtual void reload();
	virtual void update();
	virtual bool isReloading();
	virtual unsigned int getAmmo();
	virtual std::string getWeaponType();
};

