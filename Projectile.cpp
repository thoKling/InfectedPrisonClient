#include "Projectile.h"

#include "Utils.h"

Projectile::Projectile()
{
	if (!_texture.loadFromFile("Ressources/projectile.png"))
		throw std::string("Impossible de charger la texture projectile.png");

	_sprite.setTexture(_texture);

	this->setOrigin(16.f, 16.f);
}


Projectile::~Projectile()
{
}


void Projectile::setDirection(const sf::Vector2f& pos, const sf::Vector2f& mousePos)
{
	double distanceX, distanceY, a;
	double direction[2];

	// Calcul des distances x et y
	distanceX = mousePos.x - pos.x;
	distanceY = mousePos.y - pos.y;

	// Changement des valeurs de _x et de _y en fonction du quadrant et des distances x et y
	int quadrant = Utils::getQuadrant(pos, mousePos);
	switch (quadrant)
	{
		case 1:
			if (abs(distanceX) >= abs(distanceY))
			{
				a = distanceY / distanceX;
				_x = _velocity;
				_y = a * _x;
			}

			else
			{
				a = distanceX / distanceY;
				_y = -_velocity;
				_x = a * _y;
			}
			break;

		case 2:
			if (abs(distanceX) >= abs(distanceY))
			{
				a = distanceY / distanceX;
				_x = _velocity;
				_y = a * _x;
			}

			else
			{
				a = distanceX / distanceY;
				_y = _velocity;
				_x = (a * _y);
			}
			break;

		case 3:
			if (abs(distanceX) >= abs(distanceY))
			{
				a = distanceY / distanceX;
				_x = -_velocity;
				_y = a * _x;
			}

			else
			{
				a = distanceX / distanceY;
				_y = _velocity;
				_x = a * _y;
			}
			break;

		case 4:
			if (abs(distanceX) >= abs(distanceY))
			{
				a = distanceY / distanceX;
				_x = -_velocity;
				_y = a * _x;
			}

			else
			{
				a = distanceX / distanceY;
				_y = -_velocity;
				_x = a * _y;
			}
			break;
	}
}


void Projectile::update(const sf::Vector2f& mousePos)
{
	move(_x, _y);
}