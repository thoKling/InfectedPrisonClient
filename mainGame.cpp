#include "mainGame.h"

#include <string>
#include <iostream>

#include "TextureManager.h"
#include "World.h"
#include "SocketManager.h"
#include "Application.h"

mainGame::mainGame(std::string playerName, bool online)
{
	World::init(&Application::getWindow(), playerName);

	if (online) {
		SocketManager::init(playerName, "localhost", 9999);
	}
	else {

		World::getInstance()->loadMap(sf::Vector2i(0, 0));
	}
	_gameOverSprite.setTexture(*TextureManager::loadText("Ressources/gameOver.png"));
	_gameOverSprite.setScale(0.25, 0.25);
}

mainGame::~mainGame()
{
}

void mainGame::update()
{
	World::getInstance()->update();
}

void mainGame::handleInputs(const sf::Vector2f& mousePos, const sf::Event& event)
{
	World::getInstance()->handleInputs(mousePos, event);
}

void mainGame::manageDraw(sf::RenderWindow& window)
{
	World::getInstance()->draw();
}
