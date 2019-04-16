#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#define MS_PER_UPDATE 1000/60

class Application
{
public:
	Application();
	~Application();

	void start();

private:
	void draw();
	void handleInputs(sf::Event);
	void update();

	sf::Sprite _gameOverSprite;

	sf::RenderWindow _window;
};

