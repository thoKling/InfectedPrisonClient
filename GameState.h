#pragma once

#include <SFML/Window.hpp>

class Application;

///
/// GameState pattern : http://gamedev.dreamnoid.com/2009/01/06/game-state-pattern/
///

class GameState
{
public:
	GameState();
	~GameState();

	virtual void update() = 0;
	virtual void handleInputs(sf::Event event) = 0;
	virtual void manageDraw() = 0;

protected:

	Application* GameMgr;
};

