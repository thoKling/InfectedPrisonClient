#pragma once
#include "DrawableEntity.h"

class Projectile : public DrawableEntity
{
public:
	Projectile(const std::string& typeWeapon);
	~Projectile();
	
	bool toDelete();

	void update();
	
private:
	double _velocity = 8.0;
	sf::Vector2f _direction;
	bool _toDelete = false;
};

