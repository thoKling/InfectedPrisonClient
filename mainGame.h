#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class mainGame : public GameState
{
public:
	mainGame(std::string playerName, bool online);
	~mainGame();
	virtual void update();
	virtual void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);
	virtual void manageDraw(sf::RenderWindow& window);
};

