#include "Application.h"

#include <iostream>

#include "World.h"
#include "AudioManager.h"

#include "Utils.h"

sf::Packet& operator >>(sf::Packet& packet, std::vector<std::vector<int>>& myVec)
{
	for (size_t i = 0; i < myVec.size(); i++)
	{
		for (size_t j = 0; j < myVec[0].size(); j++)
		{
			packet >> myVec[i][j];
		}
	}
	return packet;
}

Application::Application()
{
	// on crée la fenêtre
	_window.create(sf::VideoMode(1024, 512), "Infected Prison");

	World::init(&_window);

	std::vector<std::vector<int>> _level;

	// Mettre à true si on veut utiliser le serveur
	bool online = false;
	if (online) {
		// on bind la socket
		if (_socket.bind(10000) != sf::Socket::Done)
		{
			throw std::string("Impossible de lié la socket au port 9999");
		}
		sf::Packet packet;
		packet << "Je suis la";
		_socket.send(packet, "localhost", 9999);

		unsigned short port;
		sf::Packet packet2;
		if (_socket.receive(packet2, _serverIP, port) != sf::Socket::Done)
		{
			throw std::string("Erreur lors de la récéption du paquet");
		}
		// on définit le niveau à l'aide de numéro de tuiles
		_level.resize(8);
		for (size_t i = 0; i < _level.size(); i++)
		{
			_level[i].resize(16);
		}
		packet2 >> _level;
	}
	else {
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
	}
	World::getInstance()->loadMap(_level, sf::Vector2i(0,0));
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

	World::getInstance()->draw();

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

	World::getInstance()->handleInputs(event);
}

// On update chaque élément du jeux (1 fois par frame)
void Application::update()
{
	// Récupération de la position de la souris par rapport à la fenêtre
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_window);

	// Conversion en coordonnées "monde"
	sf::Vector2f mouseWorldPos = _window.mapPixelToCoords(mousePixelPos);

	World::getInstance()->update(mouseWorldPos);
}
