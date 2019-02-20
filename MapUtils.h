#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#define TILESIZE 64
#define NULLPOS sf::Vector2i(-9999,-9999)

class MapUtils
{
public:
	static std::list<sf::Vector2i> getPath(const std::vector<std::vector<int>>& tiles, const sf::Vector2i& startCell, const sf::Vector2i& endCell);
	static sf::Vector2i transformInTilesPos(const sf::Vector2f& pos);
private:

};