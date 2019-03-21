#pragma once

#include <SFML/Graphics.hpp>
#include "Zombie.h"

class World;

class ZombiesManager
{
public:
	static unsigned int createZombie(const sf::Vector2f& pos);
	static std::map<unsigned int, Zombie*>& getZombies();
	static void manageDraw(sf::RenderWindow& window);
	static void update();
	static void destroyZombies();

private:
	static std::map<unsigned int, Zombie*> _zombies;
	static unsigned int _nextId;
};

