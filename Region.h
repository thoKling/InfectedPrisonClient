#pragma once

#include "TileMap.h"

class Region
{
public:
	Region(const std::vector<std::vector<int>>& tiles);
	~Region();

	void manageDraw(sf::RenderWindow& window);

	///
	/// Utils
	///
	bool isObstacle(sf::Vector2i tilePos);
	const std::vector<std::vector<int>>& getTiles() const;
	int getTileNumber(sf::Vector2i tilePos);

private:
	TileMap _map;

	std::vector<std::vector<int>> _tiles;
};

