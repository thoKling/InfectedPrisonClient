#include "Weapon.h"
#include <iostream>



Weapon::Weapon() : _capacity(5), _fireRate(10), _reloadSpeed(2), _type("gun"), _isReloading(false),_tickSinceReloadingUpdate(0), 
_tickSinceFiringUpdate(0), _isFireable(true), _needToReload(false)
{
	_ammo = _capacity;
}

Weapon::~Weapon()
{
}

// Tir du personnage
void Weapon::fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, const sf::Vector2f& firingPosition)
{
	if (_isFireable) {
		if (_ammo > 0) {
			_isFireable = false;
			projectilesManager.createProjectile(firingPosition, mousePos, _type);
			AudioManager::playSound("gunShot");
			--_ammo;
		}
		else {
			AudioManager::playSound("dryFireGunShot");
			_needToReload = true;
		}
	}
}

bool Weapon::needToReload() {
	return _needToReload;
}

bool Weapon::isReloading() {
	return _isReloading;
}

void Weapon::reload() {
	_isReloading = true;
	_needToReload = false;
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
