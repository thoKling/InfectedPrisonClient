#include "Weapon.h"

#include <iostream>

#include "ProjectilesManager.h"
#include "AudioManager.h"
#include "Player.h"
#include "TextureManager.h"

Weapon::Weapon() :
	_capacity(5),
	_fireRate(10),
	_reloadSpeed(2),
	_type(ItemType::Gun),
	_isReloading(false),
	_tickSinceReloadingUpdate(0),
	_tickSinceFiringUpdate(0),
	_isFireable(true)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/gun.png"));
	_sprite.setScale({0.083, 0.083});
	_ammo = _capacity;
}

Weapon::~Weapon()
{
}

void Weapon::use(Player* charac)
{
	if (_isFireable && !_isReloading) {
		if (_ammo > 0) {
			_isFireable = false;
			ProjectilesManager::createProjectile(charac->getPosition(), charac->getRotation(), _type);
			AudioManager::playSound("gunShot");
			--_ammo;
		}
		else {
			AudioManager::playSound("dryFireGunShot");
		}
	}
}

bool Weapon::isReloading() {
	return _isReloading;
}

unsigned int Weapon::reload(unsigned int stack) {
	unsigned int res = std::min(_capacity - _ammo, (int)stack);
	_ammo += res;
	if(res != 0)
		_isReloading = true;
	return res;
}

void Weapon::update()
{	
	/*
		On update pour le rechargement de l'arme
	*/
	// 60 frames/secondes, @see Application.h
	if (_isReloading) {
		_tickSinceReloadingUpdate++;
		if (_tickSinceReloadingUpdate > 60 * _reloadSpeed) {
			_isReloading = false;
			_tickSinceReloadingUpdate = 0;
		}
	}

	/*
		On update pour le rechargement de l'arme
	*/
	if (!_isFireable) {
		_tickSinceFiringUpdate++;
		if (_tickSinceFiringUpdate > 60 / _fireRate) {
			_isFireable = true;
			_tickSinceFiringUpdate = 0;
		}
	}
}

unsigned int Weapon::getAmmo()
{
	return _ammo;
}

ItemType Weapon::getItemType() {
	return getType();
}

ItemType Weapon::getType()
{
	return ItemType::Gun;
}
