#include "PlayersManager.h";
#include "PlayerController.h";
#include "Player.h";

#include <iostream>

#include "World.h"
#include "InventoryView.h"

unsigned int PlayersManager::_nextId = 0;
std::map<unsigned int, PlayerController*> PlayersManager::_players;

// on désalloue la mémoire utilisée pour stocker les personnages
void PlayersManager::destroyChars()
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		delete it->second;
	}
}


// créer un nouveau personnage et renvoit l'id de ce dernier
unsigned int PlayersManager::createPlayer(const sf::Vector2f& pos) {
	Player* player = new Player();
	_players[_nextId] = new PlayerController(player);
	_players[_nextId]->getPlayer()->setPosition(pos);
	_nextId++;
	return _nextId - 1;
}

// renvoit la liste des personnages
std::map<unsigned int, PlayerController*> PlayersManager::getPlayers()
{
	return _players;
}


// on draw chaque personnage
void PlayersManager::manageDraw(sf::RenderWindow& window) {
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->manageDraw(window);
	}
}

void PlayersManager::handleInputs(const sf::Event& event) {
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->handleInputs(event);
	}
}

// Mise à jour du comportement des personnages
void PlayersManager::update(const sf::Vector2f& mousePos)
{
	_players[0]->update(mousePos);
}