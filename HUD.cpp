#include "HUD.h"

#include "TextureManager.h"

sf::Sprite HUD::_spriteHeart;
sf::Sprite HUD::_spriteAmmo;
unsigned int HUD::_lives;
unsigned int HUD::_ammo;

void HUD::init(sf::RenderWindow* window)
{
	_spriteHeart.setTexture(*TextureManager::loadText("Ressources/heart.png"));
	_spriteHeart.setScale({ 0.25f, 0.25f });
	_spriteAmmo.setTexture(*TextureManager::loadText("Ressources/bullet.png"));
}

void HUD::manageDraw(sf::RenderWindow * window)
{
	for (unsigned int i = 1; i < _lives+1; ++i) {
		_spriteHeart.setPosition(window->getSize().x - (i*64), window->getSize().y - 64);
		window->draw(_spriteHeart);
	}
	for (unsigned int i = 1; i < _ammo + 1; ++i) {
		_spriteAmmo.setPosition(window->getSize().x - (i * 20), window->getSize().y - 96);
		window->draw(_spriteAmmo);
	}
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

void HUD::setWave(unsigned int wave)
{
	_currentWave = wave;
}
