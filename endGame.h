#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "TextBox.h"

class endGame : public GameState
{
public:
	endGame();
	~endGame();
	virtual void update() {  };
	virtual void handleInputs(const sf::Vector2f& mousePos, const sf::Event& event);
	virtual void manageDraw(sf::RenderWindow& window);
private:
	sf::Sprite _gameOverSprite;

	sf::Font _font;
	sf::Text _btnMenu;
	sf::Text _btnQuit;
};

