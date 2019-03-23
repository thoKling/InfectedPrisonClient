#pragma once
#include "DrawableEntity.h"

#include "Item.h"

class Projectile : public DrawableEntity
{
public:
	Projectile(const WeaponType& typeWeapon);
	~Projectile();
	
	bool toDelete();

	void update();
	
private:
	double _velocity = 8.0;
	double _travelledDistance = 0.0;
	sf::Vector2f _direction;
	bool _toDelete = false;
};

