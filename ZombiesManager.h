#pragma once

#include <SFML/Graphics.hpp>
#include "Zombie.h"

class ZombiesManager
{
public:
	static unsigned int createZombie(const sf::Vector2f& pos);
	static std::map<unsigned int, Zombie*>& getZombies();
	static void manageDraw(sf::RenderWindow& window);
	static void update();
	static void destroyZombies();
	static void setState(unsigned int id, sf::Vector2f pos, float rotation);

private:
	static std::map<unsigned int, Zombie*> _zombies;
	static unsigned int _nextId;
};

