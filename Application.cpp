#include "Application.h"

#include <iostream>

#include "World.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SocketManager.h"

#include "Menu.h"
#include "Utils.h"

std::stack<GameState*> Application::_states;
sf::RenderWindow Application::_window;

Application::Application()
{
	// on crée la fenêtre
	_window.create(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "Infected Prison");
	setState(new Menu());
}

Application::~Application()
{
}

void Application::start() {	
	// on lance la musique principale du jeu
	//AudioManager::playMainTheme();

	// on fait tourner la boucle principale
	sf::Clock clock;
	sf::Time lag = sf::seconds(0.0f);
	while (_window.isOpen())
	{
		lag += clock.getElapsedTime();
		clock.restart();
		// on gère les évènements
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_window.close();
				if (SocketManager::isOnline())
					SocketManager::stop();
			}
			handleInputs(event);
		}
		// On update
		// Game Pattern : gameLoop : http://gameprogrammingpatterns.com/game-loop.html
		while (lag.asMilliseconds() >= MS_PER_UPDATE) {
			update();
			lag -= sf::milliseconds(MS_PER_UPDATE);
		}
		// On dessine
		draw();
	}
}

// Fonction de dessin
void Application::draw()
{
	// On nettoie la fenetre
	_window.clear();

	GameState* currentGameState = getCurrentState();
	if (currentGameState != NULL) {
		currentGameState->manageDraw(_window);
	}
	// On affiche les dessins
	_window.display();
}


// Ici on gère les entrées clavier du joueur
void Application::handleInputs(sf::Event event)
{
	if (!_window.hasFocus()) {
		return;
	}

	// Toggle debugMode
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
	{
		Utils::debugMode = !Utils::debugMode;
	}

	// Récupération de la position de la souris par rapport à la fenêtre
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_window);

	// Conversion en coordonnées "monde"
	sf::Vector2f mouseWorldPos = _window.mapPixelToCoords(mousePixelPos);

	GameState* currentGameState = getCurrentState();
	if (currentGameState != NULL) {
		currentGameState->handleInputs(mouseWorldPos, event);
	}
}

// On update chaque élément du jeux (1 fois par frame)
void Application::update()
{
	GameState* currentGameState = getCurrentState();
	if (currentGameState != NULL) {
		currentGameState->update();
	}
}

void Application::pushState(GameState* state)
{
	// set current state
	_states.push(state);
}

void Application::setState(GameState* state)
{
	// Delete the actual current state (if any)
	popState();

	// Add the new state
	pushState(state);
}

void Application::popState()
{
	if (!_states.empty())
	{
		_states.pop();
	}
}

sf::RenderWindow & Application::getWindow()
{
	return _window;
}
