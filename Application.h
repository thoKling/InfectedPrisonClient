#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "TileMap.h"
#include "CharactersManager.h"
#include "ZombiesManager.h"

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

	sf::View _minimapView; // Vue de la minicarte centrée sur le personnage
	void drawMinimap();

	sf::View _mainView; // Vue principale centrée sur le personnage 

	// Systeme de lumieres
	ltbl::LightSystem _ls;
	sf::Sprite _lightSprite;
	sf::RenderStates _lightRenderStates;
	sf::Texture _penumbraTexture;
	sf::Shader _unshadowShader;
	sf::Shader _lightOverShapeShader;

	TileMap _map;
	CharactersManager _charactersManager;
	ZombiesManager _zombiesManager;

	sf::RenderWindow _window;
	sf::UdpSocket _socket;
	sf::IpAddress _serverIP;

	static void toggleDebug();
	static bool _debugMode;
};

