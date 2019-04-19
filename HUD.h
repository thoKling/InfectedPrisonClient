#pragma once

#include <SFML/Graphics.hpp>

class HUD 
{
public:
	static void init(sf::RenderWindow* window);
	static void manageDraw(sf::RenderWindow* window);
	static void setLives(unsigned int lives);
	static void setAmmo(unsigned int ammo);
	static void setZombiesLeft(unsigned int nbZombies);
	static void setWave(unsigned int wave);

private:
	static sf::Sprite _spriteHeart;
	static sf::Sprite _spriteAmmo;
	static unsigned int _lives;
	static unsigned int _ammo;
	static unsigned int _currentWave;
	static unsigned int _zombiesLeft;
	static sf::Font _font;
	static sf::Text _txtWave;
	static sf::Text _txtZombiesLeft;
};

