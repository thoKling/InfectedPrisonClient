#include "Character.h"

#include "Utils.h"
#include "MapUtils.h"
#include "World.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "LTBL2/lighting/LightSystem.h"
#include "Item.h"
#include "HUD.h"

#include <string>
#include <iostream>

Character::Character() : 
	_isPunching(false), 
	_punchingSpeed(0.5), 
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


Character::~Character()
{
	delete _currentItem;
}

/** Récupération et traitement des entrées clavier du joueur **/
void Character::handleInputs(const sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if(_currentItem)
			_currentItem->use(this);

	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//	_fire = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_dIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_qIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_sIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_upIsHeld = true;


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_dIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_qIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_sIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_upIsHeld = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		reload();

	if (event.type == sf::Event::KeyReleased)
		switch (event.key.code) {
			case sf::Keyboard::E:
				pickItem();
				break;
			case sf::Keyboard::F:
				dropItem();
				break;
		}
}

/** Déplacements du personnage **/
void Character::mv()
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

void Character::receiveHit(const sf::Vector2f& hitterPosition)
{
	if (!_beingHit && _alive) {
		_sprite.setColor(sf::Color::Red);
		_beingHit = true;
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
		if (!_lives)
			die();
	}
}

void Character::update(const sf::Vector2f& mousePos)
{	
	orientate(sf::Vector2f(mousePos));

	mv();

	light->_emissionSprite.setPosition(getPosition());

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 5, _sprite.getColor().b + 5));
		if (_sprite.getColor().g == 255)
			_beingHit = false;
	}


	// 60 frames/secondes, @see Application.h
	if (_isPunching ) {
		_tickSincePunchingUpdate++;
		if (_tickSincePunchingUpdate > 60 * _punchingSpeed) {
			_isPunching= false;
			//if(!_canPunch)
				_tickSincePunchingUpdate = 0;
		}
	}
	std::string file = "Man Blue/manBlue_stand";
	if (_currentItem) {
		_currentItem->update();
		if (_currentItem->isReloading())
			file = "Man Blue/manBlue_reload";
		else
			file = "Man Blue/manBlue_" + WeaponTypesStr[_currentItem->getWeaponType()];
		HUD::setAmmo(_currentItem->getAmmo());
	}
	else if (_isPunching) {
		file = "Man Blue/manBlue_punch";
	}
	else
		HUD::setAmmo(0);

	_sprite.setTexture(*TextureManager::loadText("Ressources/PNG/" + file + ".png"));

	HUD::setLives(_lives);
}

void Character::die()
{
	_alive = false;
}

void Character::reload()
{
	if (_currentItem) {
		WeaponType typeW = _currentItem->getWeaponType();
		unsigned int usedAmmos = _currentItem->reload(_inventory.getAmmos(typeW));
		_inventory.setAmmos(typeW, usedAmmos);
	}
}

void Character::pickItem() {
	Item* item = World::getInstance()->getItemInRect(getGlobalBounds());

	if (item != nullptr) {
		_inventory.AddItem(item);
		if(item->getWeaponType() != WeaponType::NaW)
			_currentItem = item;
	}
}

void Character::dropItem() {
	if (_currentItem) {
		World::getInstance()->dropItem(_currentItem, getPosition());
		_inventory.dropItem(_currentItem);
		_currentItem = nullptr;
	}
}