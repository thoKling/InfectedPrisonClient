#include "ZombiesManager.h"

#include "CharactersManager.h"

#include <iostream>

ZombiesManager::ZombiesManager(TileMap* map, CharactersManager* charManager) : _map(map), _nextId(0), _charManager(charManager)
{
}

// on d�salloue la m�moire utilis�e pour stocker les zombies
ZombiesManager::~ZombiesManager()
{
	for (auto it = _zombies.begin(); it != _zombies.end(); ++it)
	{
		delete it->second;
	}
}

// cr�� un nouveau zombie et renvoit l'id de ce dernier
unsigned int ZombiesManager::createZombie(const sf::Vector2f& pos) {
	_zombies[_nextId] = new Zombie(_map, _charManager);
	_zombies[_nextId]->setPosition(pos);
	_nextId++;
	return _nextId - 1;
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
	for (auto it = _zombies.begin(); it != _zombies.end(); ++it)
	{
		it->second->update();
	}
}