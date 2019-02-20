#pragma once
#include "DrawableEntity.h"

class Projectile : public DrawableEntity
{
public:
	Projectile(const std::string typeWeapon);
	~Projectile();
	
	void setDirection(const sf::Vector2f& pos, const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	
private:
	double _velocity = 6.0;
	double _x = 0.0;
	double _y = 0.0;
};

