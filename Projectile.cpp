#include "Projectile.h"

#include "Utils.h"
#include "TextureManager.h"
#include "ZombiesManager.h"

Projectile::Projectile(const WeaponType& typeWeapon)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/projectile_" + WeaponTypesStr[typeWeapon] + ".png"));

	this->setOrigin(16.f, 16.f);
}

Projectile::~Projectile()
{
}

bool Projectile::toDelete()
{
	return _toDelete;
}

void Projectile::update()
{
	move(_velocity*cos(getRotation()*toRadians), _velocity*sin(getRotation()*toRadians));
	auto zombies = ZombiesManager::getZombies();
	for (auto it = zombies.begin(); it != zombies.end(); ++it)
	{
		if (it->second->getGlobalBounds().intersects(getGlobalBounds())) {
			it->second->receiveHit(getPosition());
			_toDelete = true;
			break;
		}
	}
}