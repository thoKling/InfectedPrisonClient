#include "Zombie.h"

#include <iostream>

#include "MapUtils.h"
#include "World.h"
#include "Utils.h"
#include "PlayersManager.h"
#include "PlayerController.h"
#include "Player.h"
#include "TextureManager.h"
#include "SocketManager.h"

Zombie::Zombie() : 
	_velocity(2), 
	_lastTileTarget(NULLPOS)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/PNG/zombie/zombie.png"));
	_target = sf::Vector2f(200, 200);
	setOrigin(24.f, 24.f);
}

Zombie::~Zombie()
{

}

void Zombie::update() {
	_target = PlayersManager::getClientPlayer()->getPosition();

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 15, _sprite.getColor().b + 15));
		if (_sprite.getColor().g == 255)
			_beingHit = false;
	}
	
	if (!SocketManager::isOnline()) {
		// Si on est � distance on attaque
		if (Utils::distance(getPosition(), _target) > 80)
			myMove();
		else
			PlayersManager::getClientPlayer()->receiveHit(getPosition());
	}
}
void Zombie::receiveHit(sf::Vector2f hitterPosition)
{
	if (!_beingHit) {
		_sprite.setColor(sf::Color::Red);
		_beingHit = true;
		if (!SocketManager::isOnline()) {
			sf::Vector2f newPos;
			sf::Vector2f vecUnit = Utils::getVecUnit(hitterPosition, getPosition());
			for (size_t i = 0; i < 20; i++)
			{
				move(vecUnit.x * 5, 0);
				if (isInObstacle()) {
					move(-vecUnit.x * 5, 0);
					break;
				}
			}
			for (size_t i = 0; i < 20; i++)
			{
				move(0, vecUnit.y * 5);
				if (isInObstacle()) {
					move(0, -vecUnit.y * 5);
					break;
				}
			}
		}
		_lifes--;
	}
}

bool Zombie::isDead()
{
	return _lifes == 0;
}

// Red�finition de la m�thode draw
void Zombie::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// On dessine la zone d'attaque du zombie
	if (Utils::debugMode) {
		sf::CircleShape attackCircle(90.f);
		attackCircle.setFillColor(sf::Color(250, 0, 0, 128));
		attackCircle.setPosition(this->getPosition().x - 90, this->getPosition().y - 90);
		target.draw(attackCircle);
	}
	DrawableEntity::draw(target, states);
}

void Zombie::myMove() {

	orientate(_target);
	// On se d�place vers la destination
	sf::Vector2f vecUnit = Utils::getVecUnit(getPosition(), _target);

	this->move(vecUnit.x * _velocity, 0);
	if (isInObstacle()) {
		this->move(-vecUnit.x * _velocity, 0);
	}

	this->move(0, vecUnit.y*_velocity);
	if (isInObstacle()) {
		this->move(0, -vecUnit.y * _velocity);
	}
}

