#pragma once

#include <SFML/Graphics.hpp>

class HUD 
{
public:
	static void init(sf::RenderWindow* window);
	static void manageDraw(sf::RenderWindow* window);
	static void setLives(unsigned int lives);
	static void setAmmo(unsigned int ammo);

private:
	static sf::Sprite _spriteHeart;
	static sf::Sprite _spriteAmmo;
	static unsigned int _lives;
	static unsigned int _ammo;
};

