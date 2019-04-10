#include "Player.h"
#include "Application.h"

//#include "Utils.h"
//#include "MapUtils.h"
#include "World.h"
//#include "AudioManager.h"
#include "TextureManager.h"
#include "LTBL2/lighting/LightSystem.h"
//#include "Item.h"
//#include "Inventory.h"
//#include "InventoryView.h"

#include <string>
#include <iostream>

Player::Player():
	_currentItem(nullptr)
{
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
	delete _currentItem;
}


/** Déplacements du personnage **/
void Player::mv()
{
	double x = 0, y = 0;

	if (_dIsHeld)
		x += _velocity;

	if (_qIsHeld)
		x += -_velocity;

	if (_sIsHeld)
		y += _velocity;

	if (_upIsHeld)
		y += -_velocity;

	if (x != 0 && y != 0) {
		sf::Vector2f unitVec = Utils::getVecUnit(sf::Vector2f(0,0), sf::Vector2f(x, y));
		x = _velocity * unitVec.x;
		y = _velocity * unitVec.y;
	}

	// Déplacement en x
	this->move(x, 0);
	if(isInObstacle())
		this->move(-x, 0);

	// Déplacement en y
	this->move(0, y);
	if(isInObstacle())
		this->move(0, -y);
}

void Player::update(const sf::Vector2f& mousePos)
{	
	orientate(sf::Vector2f(mousePos));

	mv();

	light->_emissionSprite.setPosition(getPosition());

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 5, _sprite.getColor().b + 5));
		if (_sprite.getColor().g == 255)
			_beingHit = false;
	}

	std::string file = "Man Blue/manBlue_stand";
	if (_currentItem) {
		_currentItem->update();
		if (_currentItem->isReloading())
			file = "Man Blue/manBlue_reload";
		else
			file = "Man Blue/manBlue_" + WeaponTypesStr[_currentItem->getWeaponType()];
	}

	_sprite.setTexture(*TextureManager::loadText("Ressources/PNG/" + file + ".png"));
}

void Player::receiveHit(const sf::Vector2f& hitterPosition)
{
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
}

Item* Player::getCurrentItem() const
{
	return _currentItem;
}
void Player::setCurrentItem(Item* item)
{
	_currentItem = item;
}

void Player::setDState(bool state)
{
	_dIsHeld = state;
}

void Player::setQState(bool state)
{
	_qIsHeld = state;
}
void Player::setSState(bool state)
{
	_sIsHeld = state;
}
void Player::setUpState(bool state)
{
	_upIsHeld = state;
}

bool Player::getHitState() const
{
	return _beingHit;
}