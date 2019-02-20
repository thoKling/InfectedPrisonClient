#include "Zombie.h"

#include <iostream>

#include "MapUtils.h"
#include "TileMap.h"
#include "CharactersManager.h"
#include "Utils.h"
#include "Application.h"

Zombie::Zombie(TileMap* map, CharactersManager* charManager) : _map(map), _charManager(charManager), _velocity(2), _lastTileTarget(NULLPOS)
{
	if (!_texture.loadFromFile("Ressources/PNG/zombie/zombie.png"))
		throw std::string("Impossible de charger la texture zombie.png");

	_sprite.setTexture(_texture);
	_target = sf::Vector2f(200, 200);
	setOrigin(24.f, 24.f);
}


Zombie::~Zombie()
{

}

void Zombie::update() {
	_target = _charManager->getCharacters().at(0)->getPosition();
	if (Utils::distance(getPosition(), _target) > 80)
		myMove();
	else
		_charManager->getCharacters().at(0)->receiveHit(getPosition());
}

// Renvoit la position par rapport aux tiles 
sf::Vector2i Zombie::getPositionTiles() {
	return MapUtils::transformInTilesPos(sf::Vector2f(getPosition().x+32, getPosition().y+32));
}

// Redéfinition de la méthode draw
void Zombie::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// On dessine la zone d'attaque du zombie
	if (Application::isDebugMode()) {
		sf::CircleShape attackCircle(90.f);
		attackCircle.setFillColor(sf::Color(250, 0, 0, 128));
		attackCircle.setPosition(this->getPosition().x - 90, this->getPosition().y - 90);
		target.draw(attackCircle);
	}
	DrawableEntity::draw(target, states);
}

void Zombie::myMove() {
	std::list<sf::Vector2i> path;

	if (_lastTileTarget == NULLPOS) {
		path = MapUtils::getPath(_map->getTiles(), MapUtils::transformInTilesPos(getPosition()), MapUtils::transformInTilesPos(_target));
		if (!path.empty()) {
			_lastTileTarget = path.front();
		}
	}
	else {
		
		// On calcule la destination de la prochaine tile
		// TODO : pour l'instant on va vers le centre mais ca fait des déplacements bizarres, à corriger
		sf::Vector2f destination = _target;//sf::Vector2f(_lastTileTarget.x * 64 + 32, _lastTileTarget.y * 64 + 32);
		orientate(_target);
		// On se déplace vers la destination
		float depX = 0;
		float depY = 0;
		if (abs(destination.x - getPosition().x) < _velocity)
			depX = 0;
		else if (destination.x < getPosition().x)
			depX = -_velocity;
		else
			depX = _velocity;

		if (abs(destination.y - getPosition().y) < _velocity)
			depY = 0;
		else if (destination.y < getPosition().y)
			depY = -_velocity;
		else
			depY = _velocity;

		if (!depX && !depY)
			_lastTileTarget = NULLPOS;
		else
			this->move(depX, depY);
	}

	/*
	std::cout << "Pos init : " << this->getPositionTiles().x << " " << this->getPositionTiles().y << std::endl;
	while(!path.empty()) {
		std::cout << path.front().x << " " << path.front().y << std::endl;
		path.pop_front();
	}*/
}

