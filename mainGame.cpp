#include "mainGame.h"

#include <string>
#include <iostream>

#include "TextureManager.h"
#include "World.h"
#include "SocketManager.h"

mainGame::mainGame()
{
	// Mettre à true si on veut utiliser le serveur
	bool online = false;

	std::string playerName;
	std::cin >> playerName;
	//World::init(&_window, playerName);

	if (online) {
		SocketManager::init(playerName, "localhost", 9999);
	}
	else {
		std::vector<std::vector<int>> _level;
		for (size_t i = 0; i < 16; i++)
		{
			std::vector<int> temp;
			for (size_t j = 0; j < 32; j++)
			{
				if (j == 0 || j == 31 || i == 0 || i == 15)
					temp.push_back(41);
				else if (j == 5 && (i <= 5))
					temp.push_back(41);
				else
					temp.push_back(10);
			}
			_level.push_back(temp);
		}
		World::getInstance()->loadMap(sf::Vector2i(0, 0));
	}
	_gameOverSprite.setTexture(*TextureManager::loadText("Ressources/gameOver.png"));
	_gameOverSprite.setScale(0.25, 0.25);
}

mainGame::~mainGame()
{
}

void mainGame::update(sf::Vector2f mousePos)
{
	World::getInstance()->update(mousePos);
}

void mainGame::handleInputs(sf::Event event)
{
	World::getInstance()->handleInputs(event);
}

void mainGame::manageDraw()
{
	World::getInstance()->draw();
}
