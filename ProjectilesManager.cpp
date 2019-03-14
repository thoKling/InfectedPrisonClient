#include "ProjectilesManager.h"

#include <iostream>

#include "TileMap.h"

unsigned int ProjectilesManager::_nextId = 0;
std::map<unsigned int, Projectile*> ProjectilesManager::_projectiles;

// on désalloue la mémoire utilisée pour stocker les Projectiles
void ProjectilesManager::deleteAllProjectiles()
{
	for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		delete it->second;
	}
	_nextId = 0;
}


// créer un nouveau projectile et renvoit l'id de ce dernier
unsigned int ProjectilesManager::createProjectile(const sf::Vector2f& pos, const sf::Vector2f& mousePos, const std::string typeWeapon, TileMap* map) {
	_projectiles[_nextId] = new Projectile(typeWeapon, map->getZombiesManager());
	_projectiles[_nextId]->setPosition(pos);
	_projectiles[_nextId]->setDirection(mousePos);
	_nextId++;
	return _nextId - 1;
}


// on draw chaque projectile
void ProjectilesManager::manageDraw(sf::RenderWindow& window) {
	for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		window.draw(*it->second);
	}
}


// Mise à jour du comportement des projectiles
void ProjectilesManager::update(const sf::Vector2f& mousePos)
{
	std::vector<unsigned int> toErase;
	for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		it->second->update(mousePos);
		if (it->second->toDelete())
			toErase.push_back(it->first);
	}
	for (auto it = toErase.begin(); it != toErase.end(); ++it)
	{
		_projectiles.erase(*it);
	}
}