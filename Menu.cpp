#include "Menu.h"
#include "Application.h"
#include "mainGame.h"

Menu::Menu()
{
	sf::RenderWindow& window = Application::getWindow();
	// création du menu
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");

	// Titre
	_title.setFont(_font);
	_title.setString("Menu principal");
	_title.setCharacterSize(48);
	_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	_title.setOrigin(_title.getLocalBounds().left + _title.getLocalBounds().width / 2, 0);
	_title.setPosition(window.getSize().x / 2, 0);

	// Bouton "solo"
	_btnSolo.setFont(_font);
	_btnSolo.setString("Solo");
	_btnSolo.setCharacterSize(24);
	_btnSolo.setOrigin(_btnSolo.getLocalBounds().left + _btnSolo.getLocalBounds().width / 2, 0);
	_btnSolo.setPosition(window.getSize().x / 2, 150);

	// Bouton "multijoueur"
	_btnMulti.setFont(_font);
	_btnMulti.setString("Multijoueur");
	_btnMulti.setCharacterSize(24);
	_btnMulti.setOrigin(_btnMulti.getLocalBounds().left + _btnMulti.getLocalBounds().width / 2, 0);
	_btnMulti.setPosition(window.getSize().x / 2, 250);

	// Bouton "options"
	_btnSettings.setFont(_font);
	_btnSettings.setString("Options");
	_btnSettings.setCharacterSize(24);
	_btnSettings.setOrigin(_btnSettings.getLocalBounds().left + _btnSettings.getLocalBounds().width / 2, 0);
	_btnSettings.setPosition(window.getSize().x / 2, 350);

	// Textbox
	_textBox.setSize(200, 30);
	_textBox.setPosition(window.getSize().x / 2 - (_textBox.getHitBox().width / 2), 75);
}

Menu::~Menu()
{
}

void Menu::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	// Si la souris est sur le bouton "solo"
	if (_btnSolo.getGlobalBounds().contains(mousePos))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Application::pushState(new mainGame(_textBox.getStr(), false));
		}
	}

	// Si la souris est sur le bouton "multijoueur" 
	if (_btnMulti.getGlobalBounds().contains(mousePos))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Application::pushState(new mainGame(_textBox.getStr(), true));
		}
	}

	// Si la souris est sur le bouton "options" 
	if (_btnSettings.getGlobalBounds().contains(mousePos))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			// ouverture des options
		}
	}

	// TextBox
	if (_textBox.getHitBox().contains(mousePos) 
		&& event.type == sf::Event::MouseButtonPressed 
		&& event.mouseButton.button == sf::Mouse::Left) {
		_textBox.setFocus();
	}
	_textBox.handleInputs(event, mousePos);
}


void Menu::manageDraw(sf::RenderWindow& window)
{
	window.draw(_title);
	window.draw(_btnSolo);
	window.draw(_btnMulti);
	window.draw(_btnSettings);
	window.draw(_textBox);
}
