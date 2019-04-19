#include "HUD.h"

#include "TextureManager.h"

sf::Sprite HUD::_spriteHeart;
sf::Sprite HUD::_spriteAmmo;
unsigned int HUD::_lives;
unsigned int HUD::_ammo;
unsigned int HUD::_currentWave = 1;
unsigned int HUD::_zombiesLeft = 0;
sf::Font HUD::_font;
sf::Text HUD::_txtWave;
sf::Text HUD::_txtZombiesLeft;

void HUD::init(sf::RenderWindow* window)
{
	_spriteHeart.setTexture(*TextureManager::loadText("Ressources/heart.png"));
	_spriteHeart.setScale({ 0.25f, 0.25f });
	_spriteAmmo.setTexture(*TextureManager::loadText("Ressources/bullet.png"));
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
	{
		throw std::string("Impossible de charger la police");
	}
	_txtWave.setFont(_font);
	_txtWave.setCharacterSize(24);
	_txtWave.setString(" Vague : " + std::to_string(_currentWave) + " ");
	_txtZombiesLeft.setFont(_font);
	_txtZombiesLeft.setCharacterSize(18);
	_txtZombiesLeft.setString(" Zombies restant : " + std::to_string(_zombiesLeft) + " ");
	_txtZombiesLeft.setPosition(window->getSize().x - _txtZombiesLeft.getGlobalBounds().width, _txtWave.getGlobalBounds().height);
	_txtWave.setPosition(window->getSize().x - _txtWave.getGlobalBounds().width, 0);
}

void HUD::manageDraw(sf::RenderWindow * window)
{
	for (unsigned int i = 1; i < _lives+1; ++i) {
		_spriteHeart.setPosition(window->getView().getSize().x - (i*64), window->getView().getSize().y - 64);
		window->draw(_spriteHeart);
	}
	for (unsigned int i = 1; i < _ammo + 1; ++i) {
		_spriteAmmo.setPosition(window->getView().getSize().x - (i * 20), window->getView().getSize().y - 96);
		window->draw(_spriteAmmo);
	}

	_txtWave.setString(" Vague : " + std::to_string(_currentWave) + " ");
	_txtZombiesLeft.setString(" Zombies restant : " + std::to_string(_zombiesLeft) + " ");
	window->draw(_txtWave);
	window->draw(_txtZombiesLeft);
}
// Set l'adresse des vies
void HUD::setLives(unsigned int lives)
{
	_lives = lives;
}

void HUD::setAmmo(unsigned int ammo)
{
	_ammo = ammo;
}

void HUD::setZombiesLeft(unsigned int nbZombies)
{
	_zombiesLeft = nbZombies;
}

void HUD::setWave(unsigned int wave)
{
	_currentWave = wave;
}

