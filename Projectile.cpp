#include "Projectile.h"

#include "Utils.h"
#include "TextureManager.h"
#include "ZombiesManager.h"
#include "World.h"
#include "SocketManager.h"
#include "MapUtils.h"

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
	// Portée max tu projectile
	_travelledDistance += _velocity;
	if (_travelledDistance > 800)
		_toDelete = true;

	// Collisions avec les zombies
	auto zombies = ZombiesManager::getZombies();
	for (auto it = zombies.begin(); it != zombies.end(); ++it)
	{
		if (it->second->getGlobalBounds().intersects(getGlobalBounds())) {
			if (!SocketManager::isOnline()) {
				it->second->receiveHit(getPosition());
			}
			_toDelete = true;
			break;
		}
	}
	// Collisions avec les murs
	if (isInObstacle())
		_toDelete = true;
}