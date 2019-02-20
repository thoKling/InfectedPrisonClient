#include "DrawableEntity.h"

#include <iostream>

#include "Utils.h"

DrawableEntity::DrawableEntity()
{
	_texture.setSmooth(true);
}


DrawableEntity::~DrawableEntity()
{
}

// Renvoit le centre de l'entité et pas le coin en haut à gauche
sf::Vector2f DrawableEntity::getPosition() const
{
	sf::Vector2f initPos = Transformable::getPosition();
	initPos.x += _sprite.getTextureRect().width / 2 - getOrigin().x;
	initPos.y += _sprite.getTextureRect().height / 2 - getOrigin().y;
	return initPos;
}


void DrawableEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

	// on dessine le sprite
	target.draw(_sprite, states);
}

// Orientation de l'entité en direction de la position donnée
void DrawableEntity::orientate(const sf::Vector2f& position)
{
	double angle, distanceX, distanceY;

	// Récupération de la position du joueur par rapport à la fenêtre
	sf::Vector2f myPos = this->getPosition();

	// Distance entre l'entite et la position sur l'axe x
	distanceX = abs(position.x - myPos.x);

	// Distance entre l'entite et la position sur l'axe y
	distanceY = abs(position.y - myPos.y);

	// On vérifie dans quel quadrant se trouve la souris par rapport au personnage
	int quadrant = Utils::getQuadrant(position, getPosition());
	switch (quadrant) {
		case 1:
			setRotation(90.f);
			break;
		case 2:
			setRotation(180.f);
			break;
		case 3:
			setRotation(270.f);
			break;
		case 4:
			setRotation(0.f);
			break;
	}

	// S'il s'agit d'un quadrant impair, on s'attend à avoir un angle par rapport à l'axe y
	if (quadrant % 2 == 1)
	{
		if (distanceY >= distanceX)
			angle = atan(distanceX / distanceY) * toDegrees;

		// Si l'angle est par rapport à l'axe x, on soustrait cet angle à l'angle du quadrant
		else
			angle = 90 - atan(distanceY / distanceX) * toDegrees;
	}

	// S'il s'agit d'un quadrant pair, on s'attend à avoir un angle par rapport à l'axe x
	else
	{
		if (distanceX >= distanceY)
			angle = atan(distanceY / distanceX) * toDegrees;

		// Si l'angle est par rapport à l'axe y, on soustrait cet angle à l'angle du quadrant 
		else
			angle = 90 - atan(distanceX / distanceY) * toDegrees;
	}

	// On fait une rotation du personnage en fonction de l'angle final trouvé
	this->rotate(angle);
}

std::vector<sf::Vector2f> DrawableEntity::getCorners()
{
	std::vector<sf::Vector2f> res(4);
	res[0] = sf::Vector2f(getPosition().x - getOrigin().x, getPosition().y - getOrigin().y);
	res[1] = sf::Vector2f(res[0].x + _sprite.getTextureRect().width, res[0].y);
	res[3] = sf::Vector2f(res[0].x, res[0].y + _sprite.getTextureRect().height);
	res[2] = sf::Vector2f(res[1].x, res[3].y);
	return res;
}
