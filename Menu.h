#pragma once

#include <SFML/Graphics.hpp>
#include "Application.h"
#include "TextBox.h"

class Menu : public GameState
{
public:
	Menu();
	~Menu();

	void update() {  };
	void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);
	void manageDraw(sf::RenderWindow& window);

private:
	sf::Font _font;
	sf::Text _title;
	sf::Text _btnSolo;
	sf::Text _btnMulti;
	sf::Text _btnSettings;
	TextBox _textBox;

};
