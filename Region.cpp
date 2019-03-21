#include "Region.h"

#include <iostream>

Region::Region(const std::vector<std::vector<int>>& tiles)
{
	// on cr�e la tilemap avec le niveau pr�c�demment d�fini
	if (!_map.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), tiles, 32, 16))
		throw std::string("Impossible de charger la map");
	_tiles = tiles;
}


Region::~Region()
{
}

void Region::manageDraw(sf::RenderWindow & window)
{
	window.draw(_map);
}

///
/// Partie utils de la region
///

const std::vector<std::vector<int>>& Region::getTiles() const
{
	return _tiles;
}

// Renvoit le num�ro de tile
int Region::getTileNumber(sf::Vector2i tilePos)
{
	// si on demande une position en dehors de la map
	if (tilePos.x >= _tiles[0].size() || tilePos.y >= _tiles.size()) {
		std::cout << "Position demand�e en dehors de la r�gion" << std::endl;
		return -1;
	}
	return _tiles[tilePos.y][tilePos.x];
}

bool Region::isObstacle(sf::Vector2i tilePos)
{
	return getTileNumber(tilePos) == 41;
}