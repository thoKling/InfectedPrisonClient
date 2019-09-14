#include "mainGame.h"

#include <string>
#include <iostream>

#include "TextureManager.h"
#include "World.h"
#include "SocketManager.h"
#include "Application.h"
#include "endGame.h"

mainGame::mainGame(std::string playerName, bool online)
{
	World::init(&Application::getWindow(), playerName);

	if (online) {
		SocketManager::init(playerName, "169.254.102.218", 9999);
	}
	else {
		World::getInstance()->loadMap(sf::Vector2i(0, 0));
	}
}

mainGame::~mainGame()
{
}

void mainGame::update()
{
	World::getInstance()->update();
	if(World::getInstance()->getGameOver())
		Application::setState(new endGame());
}

void mainGame::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	World::getInstance()->handleInputs(mousePixelPos, mousePos, event);
}

void mainGame::manageDraw(sf::RenderWindow& window)
{
	World::getInstance()->draw();
}
