#include "Weapon.h"
#include <iostream>



Weapon::Weapon() : _capacity(10), _fireRate(1), _reloadSpeed(3), _type("gun"), _isReloading(false),_tickSinceReloadingUpdate(0), 
_tickSinceFiringUpdate(0), _isFireable(true)
{
	_ammo = _capacity;
}

Weapon::~Weapon()
{
}

// Tir du personnage
void Weapon::fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager, const sf::Vector2f& firingPosition)
{
	if (_isFireable) {
		if (_ammo > 0) {
			projectilesManager.createProjectile(firingPosition, mousePos, _type);
			audioManager._sound.play();
			--_ammo;
			_isFireable = false;
		}
		else {
			_isReloading = true;
		}
	}
}

void Weapon::update()
{
	_tickSinceReloadingUpdate++;
	_tickSinceFiringUpdate++;
	
	
	/*
		On update pour le rechargement de l'arme
	*/
	// 60 frames/secondes, @see Application.h
	if (_isReloading) {
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
		if (_tickSinceFiringUpdate > 60 / _fireRate) {
			_isFireable = true;
			_tickSinceFiringUpdate = 0;
		}
	}
}
