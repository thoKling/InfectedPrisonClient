#include "endGame.h"

#include "TextureManager.h"
#include "Application.h"*
#include "Menu.h"

endGame::endGame()
{
	_gameOverSprite.setTexture(*TextureManager::loadText("Ressources/gameOver.png"));
	_gameOverSprite.setScale(0.25, 0.25);


	sf::RenderWindow& window = Application::getWindow();
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");


	// Bouton "Menu"
	_btnMenu.setFont(_font);
	_btnMenu.setString("Menu");
	_btnMenu.setCharacterSize(36);
	_btnMenu.setOrigin(_btnMenu.getLocalBounds().left + _btnMenu.getLocalBounds().width / 2, 0);
	_btnMenu.setPosition(window.getSize().x / 3, window.getSize().y - 100);

	// Bouton "Quit"
	_btnQuit.setFont(_font);
	_btnQuit.setString("Quit");
	_btnQuit.setCharacterSize(36);
	_btnQuit.setOrigin(_btnQuit.getLocalBounds().left + _btnQuit.getLocalBounds().width / 2, 0);
	_btnQuit.setPosition( (2 * window.getSize().x) / 3, window.getSize().y - 100);
}

endGame::~endGame()
{
}

void endGame::handleInputs(const sf::Vector2f& mousePos, const sf::Event& event)
{
	// Si la souris est sur le bouton "solo"
	if (_btnMenu.getGlobalBounds().contains(mousePos))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Application::popState();
		}
	}

	// Si la souris est sur le bouton "multijoueur" 
	if (_btnQuit.getGlobalBounds().contains(mousePos))
	{
		// Et si le bouton gauche est pressé
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Application::getWindow().close();
		}
	}
}


void endGame::manageDraw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	window.draw(_gameOverSprite);

	window.draw(_btnMenu);
	window.draw(_btnQuit);

}