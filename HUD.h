#pragma once

#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();
	~HUD();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

