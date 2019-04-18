#include "ZombiesManager.h"

#include <iostream>

#include "World.h"

unsigned int ZombiesManager::_nextId = 0;
std::map<unsigned int, Zombie*> ZombiesManager::_zombies;

// on désalloue la mémoire utilisée pour stocker les zombies
void ZombiesManager::destroyZombies()
{
	for (auto it = _zombies.begin(); it != _zombies.end(); ++it)
	{
		delete it->second;
	}
}

void ZombiesManager::setState(unsigned int id, sf::Vector2f pos, float rotation)
{
	if (_zombies.find(id) != _zombies.end()) {
		_zombies[id]->setPosition(pos);
		_zombies[id]->setRotation(rotation);
	}
}

// créé un nouveau zombie et renvoit l'id de ce dernier
unsigned int ZombiesManager::createZombie(const sf::Vector2f& pos) {
	_zombies[_nextId] = new Zombie();
	_zombies[_nextId]->setPosition(pos);
	_nextId++;
	return _nextId - 1;
}

std::map<unsigned int, Zombie*>& ZombiesManager::getZombies()
{
	return _zombies;
}

// on draw chaque zombie
void ZombiesManager::manageDraw(sf::RenderWindow& window) {
	for (auto it = _zombies.begin(); it != _zombies.end(); ++it)
	{
		window.draw(*it->second);
	}
}

// on update chaque zombie
void ZombiesManager::update() {
	std::vector<unsigned int> toErase;
	for (auto it = _zombies.begin(); it != _zombies.end(); ++it)
	{
		it->second->update();
		if (it->second->isDead())
			toErase.push_back(it->first);
	}
	// On supprime les zombies morts
	for (auto it = toErase.begin(); it != toErase.end(); ++it)
	{
		_zombies.erase(*it);
	}
}