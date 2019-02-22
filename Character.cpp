#include "Character.h"

#include "Utils.h"
#include "MapUtils.h"
#include "TileMap.h"
#include "ProjectilesManager.h"
#include "AudioManager.h"
#include "Weapon.h"

#include <string>
#include <iostream>

Character::Character(TileMap* map) : _map(map)
{
	if (!_texture.loadFromFile("Ressources/zombie.png"))
		throw std::string("Impossible de charger la texture zombie.png");

	_sprite.setTexture(_texture);

	this->setOrigin(32.f, 32.f);

	_weapon = new Weapon();

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


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_rightIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_leftIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_downIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_upIsHeld = true;


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_rightIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_leftIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_downIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_upIsHeld = false;
}


/** Déplacements du personnage **/

void Character::mv()
{
	double x = 0, y = 0;

	if (_rightIsHeld)
		x += _velocity;

	if (_leftIsHeld)
		x += -_velocity;

	if (_downIsHeld)
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

void Character::update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager)
{	
	orientate(sf::Vector2f(mousePos));

	fire(mousePos, projectilesManager, audioManager);
	
	mv();

	if (_beingHit) {
		_sprite.setColor(sf::Color(_sprite.getColor().r, _sprite.getColor().g + 15, _sprite.getColor().b + 15));
		if (_sprite.getColor().g == 255)
			_beingHit = false;
	}

	_weapon->update();
}

// Tir du personnage
void Character::fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager)
{
	if (_fire)
	{
		if (_weapon) {
			_weapon->fire(mousePos, projectilesManager, audioManager, this->getPosition());
		}
	}
}

