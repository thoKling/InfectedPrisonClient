#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "GameState.h"

#include <stack>

#define MS_PER_UPDATE 1000/60

class Application
{
public:
	Application();
	~Application();

	static void start();

	/// Get the current state
	static GameState* getCurrentState() { return (!_states.empty()) ? _states.top() : NULL; }

	/// Add a new state ( become the current one )
	static void pushState(GameState* state);

	/// Set the current state
	static void setState(GameState* state);

	/// Delete the current state
	static void popState();
	static sf::RenderWindow& getWindow();

private:
	static void draw();
	static void handleInputs(sf::Event);
	static void update();
	// State manager for game states
	static std::stack<GameState*> _states;
	static sf::RenderWindow _window;
};

