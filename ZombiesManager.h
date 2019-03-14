#pragma once

#include <SFML/Graphics.hpp>
#include "Zombie.h"

class TileMap;
class CharactersManager;

class ZombiesManager
{
public:
	ZombiesManager(TileMap* map, CharactersManager* player);
	~ZombiesManager();
	unsigned int createZombie(const sf::Vector2f& pos);
	std::map<unsigned int, Zombie*>& getZombies();
	void manageDraw(sf::RenderWindow& window);
	void update();

private:
	std::map<unsigned int, Zombie*> _zombies;
	TileMap* _map;
	CharactersManager* _charManager;
	unsigned int _nextId;
};

