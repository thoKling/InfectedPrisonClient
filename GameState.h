#pragma once

#include <SFML/Graphics.hpp>

///
/// GameState pattern : http://gamedev.dreamnoid.com/2009/01/06/game-state-pattern/
///

class GameState
{
public:
	GameState();
	~GameState();

	virtual void update() = 0;
	virtual void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event) = 0;
	virtual void manageDraw(sf::RenderWindow& window) = 0;
};

