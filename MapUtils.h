#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#define NULLPOS sf::Vector2i(-9999,-9999)
#define TILESIZE 64

class MapUtils
{
public:
	static std::list<sf::Vector2i> getPath(const sf::Vector2i& startCell, const sf::Vector2i& endCell);
	static sf::Vector2i transformInTilesPos(const sf::Vector2f& pos);
};