#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class mainGame : public GameState
{
public:
	mainGame(bool online);
	~mainGame();
	virtual void update();
	virtual void handleInputs(const sf::Vector2f& mousePos, const sf::Event& event);
	virtual void manageDraw(sf::RenderWindow& window);
private:
	sf::Sprite _gameOverSprite;
};

