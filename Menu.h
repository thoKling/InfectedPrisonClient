#pragma once

#include <SFML/Graphics.hpp>
#include "Application.h"

class Menu
{
public:
	Menu();
	~Menu();

	void start();

private:
	void handleInputs(sf::Event);
	void draw();

	sf::RenderWindow _window;

	sf::Font _font;
	sf::Text _title;
	sf::Text _btnSolo;
	sf::Text _btnMulti;
	sf::Text _btnSettings;
};

