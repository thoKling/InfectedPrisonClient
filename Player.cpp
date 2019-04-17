#include "Player.h"
#include "Application.h"

#include "World.h"
#include "TextureManager.h"
#include "LTBL2/lighting/LightSystem.h"

#include <string>
#include <iostream>

Player::Player(std::string name) : _name(name)
{
	_showing = Showing::Stand;
	this->setOrigin(24.f, 24.f);

	sf::Texture* pointLightTexture = TextureManager::loadText("LTBL2/resources/pointLightTexture.png");
	light = std::make_shared<ltbl::LightPointEmission>();
	light->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture->getSize().x * 0.5f, pointLightTexture->getSize().y * 0.5f));
	light->_emissionSprite.setTexture(*pointLightTexture);
	light->_emissionSprite.setScale(sf::Vector2f(9.0f, 9.0f));
	light->_emissionSprite.setColor(sf::Color(255, 230, 200));
	light->_emissionSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);
	World::getInstance()->getLightSys()->addLight(light);

	_sprite.setTexture(*TextureManager::loadText("Ressources/PNG/Man Blue/manBlue_stand.png"));
}


Player::~Player()
{
}



void Player::update()
{	
	light->_emissionSprite.setPosition(getPosition());

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 5, _sprite.getColor().b + 5));
		if (_sprite.getColor().g == 255)
			_beingHit = false;
	}

	std::string file = "Man Blue/manBlue_stand";
	switch (_showing) {
		case Showing::Reloading:
			file = "Man Blue/manBlue_reload";
			break;
		case Showing::Armed:
			file = "Man Blue/manBlue_gun";
			break;
	}
	_sprite.setTexture(*TextureManager::loadText("Ressources/PNG/" + file + ".png"));
}

void Player::receiveHit(const sf::Vector2f& hitterPosition)
{
	if (_beingHit)
		return;
	_beingHit = true;
	_sprite.setColor(sf::Color::Red);
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
	--_lives;
}

void Player::setShowing(Showing showing)
{
	_showing = showing;
}

std::string Player::getName()
{
	return _name;
}

unsigned int Player::getLives()
{
	return _lives;
}

bool Player::getHitState() const
{
	return _beingHit;
}

double Player::getVelocity()
{
	return _velocity;
}
