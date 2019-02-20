#include "Weapon.h"



Weapon::Weapon() : _capacity(10), _fireRate(1), _ammo(_capacity), _reloadSpeed(3), _type("gun"), isReloading(false)
{
}

Weapon::~Weapon()
{
}

// Tir du personnage
void Weapon::fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager, const sf::Vector2f& firingPosition)
{
	if (_ammo > 0) {
		projectilesManager.createProjectile(firingPosition, mousePos, _type);
		audioManager._sound.play();
		--_ammo;
	}
	else {
		this->reload();
	}
}

void Weapon::reload() 
{
	_ammo = _capacity;
	isReloading = true;
}
