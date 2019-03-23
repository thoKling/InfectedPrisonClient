#include "Projectile.h"

#include "Utils.h"
#include "TextureManager.h"
#include "ZombiesManager.h"
#include "World.h"
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
	_travelledDistance += _velocity;
	if (_travelledDistance > 800)
		_toDelete = true;
	// Collisions avec les zombies
	auto zombies = ZombiesManager::getZombies();
	for (auto it = zombies.begin(); it != zombies.end(); ++it)
	{
		if (it->second->getGlobalBounds().intersects(getGlobalBounds())) {
			it->second->receiveHit(getPosition());
			_toDelete = true;
			break;
		}
	}
	// Collisions avec les murs
	std::vector<sf::Vector2f> corners = getCorners();
	for (size_t i = 0; i < 4; i++)
	{
		if (World::getInstance()->isObstacle(MapUtils::transformInTilesPos(corners[i]))) {
			_toDelete = true;
			break;
		}
	}
}