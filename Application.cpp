#include "Application.h"

#include <iostream>

#include "LTBL2/src/LightSystem.hpp"

#include "TileMap.h"

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

Application::Application() : _zombiesManager(&_map, &_charactersManager), _charactersManager(&_map)
{
	_ls = new ltbl::LightSystem(test1, test2);
	_ls->create({ -1000.f, -1000.f, 2000.f, 2000.f }, _window.getSize());

	pointLightTexture.loadFromFile("LTBL2/examples/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	_playerLight = _ls->createLightPointEmission();
	_playerLight->setTexture(pointLightTexture);
	//_playerLight->setTextureRect(sf::IntRect{ 0,0,(int)pointLightTexture.getSize().x*2, (int)pointLightTexture.getSize().y*2 });
	_playerLight->setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	_playerLight->setScale(18.f, 18.f);
	_playerLight->setColor(sf::Color(255,255,255));
	_playerLight->setSourceRadius(20000.f);

	// on crée la fenêtre
	_window.create(sf::VideoMode(1024, 512), "Infected Prison");
	_mainView = _window.getDefaultView();
	_mainView.zoom(1.5f);
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
				else
					temp.push_back(10);
			}
			_level.push_back(temp);
		}
	}

	// on crée la tilemap avec le niveau précédemment défini
	if (!_map.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), _level, 32, 16))
		throw std::string("Impossible de charger la map");

	// on crée la musique principale du jeu
	_audioManager.createMainTheme();
	_audioManager.createSoundBuffer();
	_audioManager._buffer.loadFromFile("gun.wav");
	_audioManager._sound.setBuffer(_audioManager._buffer);

	_charactersManager.createCharacter(sf::Vector2f(300, 200));
	_zombiesManager.createZombie(sf::Vector2f(80, 300));
}


Application::~Application()
{
}

void Application::start() {	
	// on lance la musique principale du jeu
	_audioManager.playMainTheme();

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
	sf::Vector2i playerPos = sf::Vector2i(_charactersManager.getCharacters()[0]->getPosition()); // On cast en int car quand position pas exacte la vue bug

	// On nettoie la fenetre
	_window.clear();

	//_ls->render(_window);
	// On dessine la miniMap
	sf::View minimapView = _window.getDefaultView();
	// Dans un coin en haut à droite
	minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
	minimapView.zoom(2.f);
	// On centre sur le joueur
	minimapView.setCenter((int)playerPos.x, (int)playerPos.y); // On cast en int car quand position pas exacte la vue bug
	_window.setView(minimapView);

	// On fait les différents dessins en commencant par la map
	_window.draw(_map);
	_charactersManager.manageDraw(_window);
	_zombiesManager.manageDraw(_window);

	// On met à jour la vue principale centrée sur le joueur
	_mainView.setCenter(sf::Vector2f(playerPos));
	_window.setView(_mainView);

	// On fait les différents dessins en commencant par la map
	_window.draw(_map);
	_charactersManager.manageDraw(_window);
	_zombiesManager.manageDraw(_window);
	_projectilesManager.manageDraw(_window);

	_playerLight->setLocalCastCenter(_charactersManager.getCharacters()[0]->getPosition());
	_playerLight->setRotation(0.f);

	// On affiche les dessins
	_window.display();
}

// Ici on gère les entrées clavier du joueur
void Application::handleInputs(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
	{
		Application::toggleDebug();
	}
	// Récupération des entrées clavier qui concernent les personnages
	_charactersManager.handleInputs(event);
}

// On update chaque élément du jeux (1 fois par frame)
void Application::update()
{
	// Récupération de la position de la souris par rapport à la fenêtre
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_window);

	// Conversion en coordonnées "monde"
	sf::Vector2f mouseWorldPos = _window.mapPixelToCoords(mousePixelPos);

	// Mise à jour du comportement des personnages
	_charactersManager.update(mouseWorldPos, _projectilesManager, _audioManager);

	_playerLight->setPosition(_charactersManager.getCharacters()[0]->getPosition());

	// Idem avec les zombies
	_zombiesManager.update();

	// Idem avec les projectiles
	_projectilesManager.update(mouseWorldPos);
}

// Affichage de choses utiles pour dév
bool Application::_debugMode = false;
void Application::toggleDebug()
{
	Application::_debugMode = !Application::_debugMode;
}

bool Application::isDebugMode()
{
	return Application::_debugMode;
}
