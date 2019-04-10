#include "Ammo.h"

#include "TextureManager.h"

Ammo::Ammo(WeaponType ammoType)
{
	_ammoType = ammoType;
	_sprite.setTexture(*TextureManager::loadText("Ressources/ammo.png"));
	_sprite.setScale({0.125,0.25});
}


Ammo::~Ammo()
{
}

WeaponType Ammo::getAmmoType()
{
	return _ammoType;
}
