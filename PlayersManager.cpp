#include "PlayersManager.h";
#include "PlayerController.h";
#include "Player.h";

#include <iostream>

#include "World.h"
#include "InventoryView.h"

std::map<std::string, Player*> PlayersManager::_playersConnected;
Player* PlayersManager::_clientPlayer = nullptr;
PlayerController PlayersManager::_clientPlayerController;

// on désalloue la mémoire utilisée pour stocker les personnages
void PlayersManager::destroyChars()
{
	for (auto it = _playersConnected.begin(); it != _playersConnected.end(); ++it)
	{
		delete it->second;
	}
}

void PlayersManager::createClientPlayer(std::string name, const sf::Vector2f& pos)
{
	_clientPlayer = new Player(name);
	_playersConnected[name] = _clientPlayer;
	_playersConnected[name]->setPosition(pos);
	_clientPlayerController.attach(_clientPlayer);
}


// créer un nouveau personnage et renvoit l'id de ce dernier
void PlayersManager::createPlayer(std::string name, const sf::Vector2f& pos) {
	_playersConnected[name] = new Player(name);
	_playersConnected[name]->setPosition(pos);
}

// renvoit la liste des personnages
std::map<std::string, Player*> PlayersManager::getPlayers()
{
	return _playersConnected;
}

Player * PlayersManager::getPlayer(std::string name)
{
	return _playersConnected[name];
}

Player * PlayersManager::getClientPlayer()
{
	return _clientPlayer;
}

PlayerController & PlayersManager::getClientController()
{
	return _clientPlayerController;
}

// on draw chaque personnage
void PlayersManager::manageDrawCharacters(sf::RenderWindow& window) {
	for (auto it = _playersConnected.begin(); it != _playersConnected.end(); ++it)
	{
		window.draw(*it->second);
	}
}

// Mise à jour du comportement des personnages
void PlayersManager::update()
{
	_clientPlayerController.update();
	for (auto it = _playersConnected.begin(); it != _playersConnected.end(); ++it)
	{
		it->second->update();
	}
}