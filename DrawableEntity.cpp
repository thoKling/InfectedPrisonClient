#include "DrawableEntity.h"

#include <iostream>
#include "World.h"
#include "MapUtils.h"

#include "Utils.h"

DrawableEntity::DrawableEntity()
{
}


DrawableEntity::~DrawableEntity()
{

}

// Renvoit le centre de l'entit� et pas le coin en haut � gauche
sf::Vector2f DrawableEntity::getPosition() const
{
	sf::Vector2f initPos = Transformable::getPosition();
	initPos.x += _sprite.getGlobalBounds().width / 2 - getOrigin().x;
	initPos.y += _sprite.getGlobalBounds().height / 2 - getOrigin().y;
	return initPos;
}

sf::Sprite DrawableEntity::getSprite() const
{
	return _sprite;
}

void DrawableEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entit� -- on la combine avec celle qui a �t� pass�e par l'appelant
	states.transform *= getTransform(); // getTransform() est d�finie par sf::Transformable

	// on dessine le sprite
	target.draw(_sprite, states);
}

bool DrawableEntity::isInObstacle()
{
	// Gestion des collisions
	auto corners = getCorners();
	for (size_t i = 0; i < 4; i++)
	{
		if (World::getInstance()->isObstacle(MapUtils::transformInTilesPos(corners[i]))) {
			return true;
		}
	}
	return false;
}

// Orientation de l'entit� en direction de la position donn�e
void DrawableEntity::orientate(const sf::Vector2f& position)
{
	double angle, distanceX, distanceY;

	// R�cup�ration de la position du joueur par rapport � la fen�tre
	sf::Vector2f myPos = this->getPosition();

	// Distance entre l'entite et la position sur l'axe x
	distanceX = abs(position.x - myPos.x);

	// Distance entre l'entite et la position sur l'axe y
	distanceY = abs(position.y - myPos.y);

	// On v�rifie dans quel quadrant se trouve la souris par rapport au personnage
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
	// S'il s'agit d'un quadrant impair, on s'attend � avoir un angle par rapport � l'axe y
	if (quadrant % 2 == 1)
	{
		if (distanceY >= distanceX)
			angle = atan(distanceX / distanceY) * toDegrees;

		// Si l'angle est par rapport � l'axe x, on soustrait cet angle � l'angle du quadrant
		else
			angle = 90 - atan(distanceY / distanceX) * toDegrees;
	}

	// S'il s'agit d'un quadrant pair, on s'attend � avoir un angle par rapport � l'axe x
	else
	{
		if (distanceX >= distanceY)
			angle = atan(distanceY / distanceX) * toDegrees;

		// Si l'angle est par rapport � l'axe y, on soustrait cet angle � l'angle du quadrant 
		else
			angle = 90 - atan(distanceX / distanceY) * toDegrees;
	}

	// On fait une rotation du personnage en fonction de l'angle final trouv�
	this->rotate(angle);
}

// Retourne la hitBox de l'entite
sf::FloatRect DrawableEntity::getGlobalBounds()
{
	sf::FloatRect res = sf::FloatRect(
		Transformable::getPosition(),
		sf::Vector2f(_sprite.getGlobalBounds().height, _sprite.getGlobalBounds().width));
	return res;
}

std::vector<sf::Vector2f> DrawableEntity::getCorners()
{
	std::vector<sf::Vector2f> res(4);
	res[0] = sf::Vector2f(sf::Transformable::getPosition().x - getOrigin().x, sf::Transformable::getPosition().y - getOrigin().y);
	res[1] = sf::Vector2f(res[0].x + _sprite.getGlobalBounds().width, res[0].y);
	res[3] = sf::Vector2f(res[0].x, res[0].y + _sprite.getGlobalBounds().height);
	res[2] = sf::Vector2f(res[1].x, res[3].y);
	return res;
}
