#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "TileMap.h"
#include "CharactersManager.h"
#include "ZombiesManager.h"
#include "ProjectilesManager.h"
#include "AudioManager.h"


#define MS_PER_UPDATE 1000/60

class Application
{
public:
	Application();
	~Application();

	void start();
	static bool isDebugMode();

private:
	void draw();
	void handleInputs(sf::Event);
	void update();

	sf::View _mainView; // Vue centrée sur le personnage 

	TileMap _map;
	CharactersManager _charactersManager;
	ZombiesManager _zombiesManager;
	ProjectilesManager _projectilesManager;

	sf::RenderWindow _window;
	sf::UdpSocket _socket;
	sf::IpAddress _serverIP;

	static void toggleDebug();
	static bool _debugMode;
};

