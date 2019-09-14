#include "Ammo.h"

#include "TextureManager.h"

Ammo::Ammo(ItemType ammo) :
	_ammo(ammo)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/ammo.png"));
	_sprite.setScale({0.125,0.25});
}


Ammo::~Ammo()
{
}

ItemType Ammo::getAmmoType()
{
	return getType();
}

ItemType Ammo::getType()
{
	return _ammo;
}
