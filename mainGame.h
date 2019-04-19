#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class mainGame : public GameState
{
public:
	mainGame();
	~mainGame();
	virtual void update(sf::Vector2f mousePos);
	virtual void handleInputs(sf::Event event);
	virtual void manageDraw();
private:
	sf::Sprite _gameOverSprite;
};

