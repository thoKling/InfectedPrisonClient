#include "ProjectilesManager.h"

#include <iostream>

ProjectilesManager::ProjectilesManager()
{
	_nextId = 0;
}


// on désalloue la mémoire utilisée pour stocker les Projectiles
ProjectilesManager::~ProjectilesManager()
{
	for (std::map<unsigned int, Projectile*>::iterator it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		delete it->second;
	}
}


// créer un nouveau projectile et renvoit l'id de ce dernier
unsigned int ProjectilesManager::createProjectile(const sf::Vector2f& pos, const sf::Vector2f& mousePos) {
	_projectiles[_nextId] = new Projectile();
	_projectiles[_nextId]->setPosition(pos);
	_projectiles[_nextId]->orientate(mousePos);
	_projectiles[_nextId]->setDirection(pos, mousePos);
	_nextId++;
	return _nextId - 1;
}


// on draw chaque projectile
void ProjectilesManager::manageDraw(sf::RenderWindow& window) {
	for (std::map<unsigned int, Projectile*>::iterator it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		window.draw(*it->second);
	}
}


// Mise à jour du comportement des projectiles
void ProjectilesManager::update(const sf::Vector2f& mousePos)
{
	for (std::map<unsigned int, Projectile*>::iterator it = _projectiles.begin(); it != _projectiles.end(); ++it)
	{
		it->second->update(mousePos);
	}
}