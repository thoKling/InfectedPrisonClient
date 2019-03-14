#pragma once
#include "DrawableEntity.h"

class ZombiesManager;

class Projectile : public DrawableEntity
{
public:
	Projectile(const std::string typeWeapon, ZombiesManager* zombiesManager);
	~Projectile();
	
	bool toDelete();

	void setDirection(const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	
private:
	ZombiesManager* _zombiesManager;
	double _velocity = 8.0;
	sf::Vector2f _direction;
	bool _toDelete = false;

};

