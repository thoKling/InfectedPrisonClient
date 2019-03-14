#include "Weapon.h"

#include <iostream>

#include "ProjectilesManager.h"
#include "TileMap.h"

Weapon::Weapon() : _capacity(5), _fireRate(10), _reloadSpeed(2), _type("gun"), _isReloading(false),_tickSinceReloadingUpdate(0), 
_tickSinceFiringUpdate(0), _isFireable(true)
{
	_ammo = _capacity;
}

Weapon::~Weapon()
{
}

// Tir du personnage
void Weapon::fire(const sf::Vector2f& mousePos, const sf::Vector2f& firingPosition, TileMap* map)
{
	if (_isFireable) {
		if (_ammo > 0) {
			_isFireable = false;
			ProjectilesManager::createProjectile(firingPosition, mousePos, _type, map);
			AudioManager::playSound("gunShot");
			--_ammo;
		}
		else {
			AudioManager::playSound("dryFireGunShot");
		}
	}
}

bool Weapon::needToReload() {
	return _ammo == 0;
}

bool Weapon::isReloading() {
	return _isReloading;
}

void Weapon::reload() {
	_isReloading = true;
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
			_ammo = _capacity;
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

std::string Weapon::getType() {
	return _type;
}
