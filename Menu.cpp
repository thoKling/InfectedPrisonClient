#include "Menu.h"
#include "Application.h"



Menu::Menu()
{
	// création de la fenêtre
	_window.create(sf::VideoMode(1024, 512), "Infected Prison");

	// création du menu
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");

	// Titre
	_title.setFont(_font);
	_title.setString("Menu principal");
	_title.setCharacterSize(48);
	_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	_title.setOrigin(_title.getLocalBounds().left + _title.getLocalBounds().width / 2, 0);
	_title.setPosition(_window.getSize().x / 2, 0);

	// Bouton "solo"
	_btnSolo.setFont(_font);
	_btnSolo.setString("Solo");
	_btnSolo.setCharacterSize(24);
	_btnSolo.setOrigin(_btnSolo.getLocalBounds().left + _btnSolo.getLocalBounds().width / 2, 0);
	_btnSolo.setPosition(_window.getSize().x / 2, 150);

	// Bouton "multijoueur"
	_btnMulti.setFont(_font);
	_btnMulti.setString("Multijoueur");
	_btnMulti.setCharacterSize(24);
	_btnMulti.setOrigin(_btnMulti.getLocalBounds().left + _btnMulti.getLocalBounds().width / 2, 0);
	_btnMulti.setPosition(_window.getSize().x / 2, 250);

	// Bouton "options"
	_btnSettings.setFont(_font);
	_btnSettings.setString("Options");
	_btnSettings.setCharacterSize(24);
	_btnSettings.setOrigin(_btnSettings.getLocalBounds().left + _btnSettings.getLocalBounds().width / 2, 0);
	_btnSettings.setPosition(_window.getSize().x / 2, 350);
}


Menu::~Menu()
{
}

void Menu::start()
{
	// on fait tourner la boucle principale
	while (_window.isOpen())
	{
		if (_btnSolo.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
			_btnSolo.setStyle(sf::Text::Bold);
		else
			_btnSolo.setStyle(NULL);

		if (_btnMulti.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
			_btnMulti.setStyle(sf::Text::Bold);
		else
			_btnMulti.setStyle(NULL);

		if (_btnSettings.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
			_btnSettings.setStyle(sf::Text::Bold);
		else
			_btnSettings.setStyle(NULL);

		// on gère les évènements
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			handleInputs(event);
		}

		// On dessine
		draw();
	}
}

void Menu::handleInputs(sf::Event event)
{
	// Si la souris est sur le bouton "solo"
	if (_btnSolo.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			// lancement de l'application solo
			_window.close();
			Application app;
			app.start();
		}
	}

	// Si la souris est sur le bouton "multijoueur" 
	if (_btnMulti.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			// lancement de l'application multijoueur
		}
	}

	// Si la souris est sur le bouton "options" 
	if (_btnSettings.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			// ouverture des options
		}
	}
}


void Menu::draw()
{
	_window.clear();

	_window.draw(_title);
	_window.draw(_btnSolo);
	_window.draw(_btnMulti);
	_window.draw(_btnSettings);

	_window.display();
}


