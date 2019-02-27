#include "Character.h"

#include "Utils.h"
#include "MapUtils.h"
#include "TileMap.h"
#include "ProjectilesManager.h"
#include "AudioManager.h"
#include "Weapon.h"

#include <string>
#include <iostream>

Character::Character(TileMap* map) : _map(map), _isPunching(false), _punchingSpeed(0.5), _weapon(nullptr)
{
	this->setOrigin(32.f, 32.f);

}


Character::~Character()
{
}


/** Récupération et traitement des entrées clavier du joueur **/
void Character::handleInputs(const sf::Event& event)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_fire = true;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_fire = false;


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
		if (_weapon && _weapon->needToReload())
			_weapon->reload();
	if(event.type ==sf::Event::KeyReleased && event.key.code == sf::Keyboard::G)
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 
	{
		if (!_weapon) {
			this->receiveWeapon();
		}
		else {
			this->throwWeapon();
		}
	}
	
}

void Character::receiveWeapon() {
	_weapon = new Weapon();

	_sprite.setTexture(_texture);
}

void Character::throwWeapon() {

	delete _weapon;
	_weapon = nullptr;

	_sprite.setTexture(_texture);
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
	// Gestion des collisions en x
	std::vector<sf::Vector2f> corners = getCorners();
	for (size_t i = 0; i < 4; i++)
	{
		if (_map->isObstacle(MapUtils::transformInTilesPos(corners[i]))) {
			std::cout << "Can't move in x" << std::endl;
			this->move(-x, 0);
			break;
		}
	}

	// Déplacement en y
	this->move(0, y);
	// Gestion des collisions en y
	corners = getCorners();
	for (size_t i = 0; i < 4; i++)
	{
		if (_map->isObstacle(MapUtils::transformInTilesPos(corners[i]))) {
			std::cout << "Can't move in y" << std::endl;
			this->move(0, -y);
			break;
		}
	}
}

void Character::receiveHit(const sf::Vector2f& hitterPosition)
{
	if (!_beingHit) {
		_sprite.setColor(sf::Color::Red);
		_beingHit = true;
		sf::Vector2f newPos;
		sf::Vector2f vecUnit = Utils::getVecUnit(hitterPosition, getPosition());
		move(sf::Vector2f(vecUnit.x * 100, vecUnit.y * 100));	
	}
}

void Character::draw() {
	
	std::string file = "Man Blue/manBlue_stand";
	if (_weapon) {

		if(_weapon->isReloading())
			file = "Man Blue/manBlue_reload";
		else
			file = "Man Blue/manBlue_"+_weapon->getType();
	}
	else if (_isPunching) {
		file = "Man Blue/manBlue_punch";
	}
	if (!_texture.loadFromFile("Ressources/PNG/" + file + ".png"))
		throw std::string("Impossible de charger la texture " + file + ".png");

	_sprite.setTexture(_texture);
}

void Character::update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager)
{	
	orientate(sf::Vector2f(mousePos));

	fire(mousePos, projectilesManager);
	
	mv();

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 15, _sprite.getColor().b + 15));
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

	if(_weapon)
		_weapon->update();

	draw();
}

// Tir du personnage
void Character::fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager)
{
	if (_fire)
	{
		if (_weapon) {
			_weapon->fire(mousePos, projectilesManager, this->getPosition());
		}
		else {
			if(!_isPunching) 
				_isPunching = true;
		}
	}
}

