#include "PlayersManager.h";
#include "PlayerController.h";
#include "Player.h";

#include <iostream>

#include "World.h"
#include "InventoryView.h"

unsigned int PlayersManager::_nextId = 0;
std::map<unsigned int, PlayerController*> PlayersManager::_players;

// on d�salloue la m�moire utilis�e pour stocker les personnages
void PlayersManager::destroyChars()
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		delete it->second;
	}
}


// cr�er un nouveau personnage et renvoit l'id de ce dernier
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
void PlayersManager::manageDrawCharacters(sf::RenderWindow& window) {
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->manageDrawCharacter(window);
	}
}

// on draw chaque inventaire
void PlayersManager::manageDrawInventories(sf::RenderWindow& window) {
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->manageDrawInventory(window);
	}
}

void PlayersManager::handleInputs(const sf::Event& event) {
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->handleInputs(event);
	}
}

// Mise � jour du comportement des personnages
void PlayersManager::update(const sf::Vector2f& mousePos)
{
	for (auto it = _players.begin(); it != _players.end(); ++it)
	{
		it->second->update(mousePos);
	}
}