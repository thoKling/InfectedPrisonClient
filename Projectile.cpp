#include "Projectile.h"

#include "Utils.h"
#include "TextureManager.h"
#include "ZombiesManager.h"

Projectile::Projectile(const std::string& typeWeapon)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/projectile_" + typeWeapon + ".png"));

	this->setOrigin(16.f, 16.f);
}

Projectile::~Projectile()
{
}

bool Projectile::toDelete()
{
	return _toDelete;
}


void Projectile::setDirection(const sf::Vector2f& destination)
{
	orientate(destination);
	_direction = Utils::getVecUnit(getPosition(), destination);
}


void Projectile::update()
{
	move(_velocity*_direction.x, _velocity*_direction.y);
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