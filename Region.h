#pragma once

#include "TileMap.h"
#include "DroppedItem.h"

class Region
{
public:
	Region(const std::vector<std::vector<int>>& tiles);
	~Region();

	void manageDraw(sf::RenderWindow& window);
	void update();

	Item* getItemInRect(const sf::FloatRect& rect);
	void dropItem(Item* item, const sf::Vector2f& position);

	///
	/// Utils
	///
	bool isObstacle(sf::Vector2i tilePos);
	const std::vector<std::vector<int>>& getTiles() const;
	int getTileNumber(sf::Vector2i tilePos);

private:
	unsigned int _ticks = 0;
	TileMap _map;

	std::list<DroppedItem*> _items;
	std::vector<std::vector<int>> _tiles;
};

