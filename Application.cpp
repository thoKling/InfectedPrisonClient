#include "Application.h"

#include <iostream>

#include "World.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "SocketManager.h"

#include "Utils.h"

Application::Application()
{
	// on crée la fenêtre
	_window.create(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "Infected Prison");

	// Mettre à true si on veut utiliser le serveur
	bool online = false;

	std::string playerName;
	std::cin >> playerName;
	World::init(&_window, playerName);

	if (online) {
		SocketManager::init(playerName, "localhost", 9999);
	}
	else {	
		std::vector<std::vector<int>> _level;
		for (size_t i = 0; i < 16; i++)
		{
			std::vector<int> temp;
			for (size_t j = 0; j < 32; j++)
			{
				if (j == 0 || j == 31 || i == 0 || i == 15)
					temp.push_back(41);
				else if (j == 5 && (i <=5 ))
					temp.push_back(41);
				else
					temp.push_back(10);
			}
			_level.push_back(temp);
		}	
		World::getInstance()->loadMap(_level, sf::Vector2i(0,0));
	}
	_gameOverSprite.setTexture(*TextureManager::loadText("Ressources/gameOver.png"));
	_gameOverSprite.setScale(0.25, 0.25);
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
			if (event.type == sf::Event::Closed)
				_window.close();
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

	if (!World::getInstance()->getGameOver())
		World::getInstance()->draw();
	else {
		_window.setView(_window.getDefaultView());
		_window.draw(_gameOverSprite);
	}

	// On affiche les dessins
	_window.display();
}


// Ici on gère les entrées clavier du joueur
void Application::handleInputs(sf::Event event)
{
	if (!_window.hasFocus() || World::getInstance()->getGameOver()) {
		return;
	}

	// Toggle debugMode
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
	{
		Utils::debugMode = !Utils::debugMode;
	}

	World::getInstance()->handleInputs(event);
}

// On update chaque élément du jeux (1 fois par frame)
void Application::update()
{
	// Récupération de la position de la souris par rapport à la fenêtre
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_window);

	// Conversion en coordonnées "monde"
	sf::Vector2f mouseWorldPos = _window.mapPixelToCoords(mousePixelPos);

	if(!World::getInstance()->getGameOver())
		World::getInstance()->update(mouseWorldPos);
}
