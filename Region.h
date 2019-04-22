#pragma once

#include "TileMap.h"
#include "DroppedItem.h"

class Region
{
public:
	Region(const std::string& fileMap);
	Region(std::vector<std::vector<int>>& tiles);
	~Region();

	void manageDraw(sf::RenderWindow& window);
	void update();

	DroppedItem* getDroppedItemInRect(const sf::FloatRect& rect);
	void dropItem(Item* item, const sf::Vector2f& position);
	void addItem(Item* item, const sf::Vector2f& position);

	///
	/// Utils
	///
	bool isObstacle(sf::Vector2i tilePos);
	const std::vector<std::vector<int>>& getTiles() const;
	int getTileNumber(sf::Vector2i tilePos);
	void deleteItem(Item* item, const sf::Vector2f pos);

private:

	unsigned int _ticks = 0;
	TileMap _mapBase;
	TileMap _map;

	std::list<DroppedItem*> _items;
	std::vector<std::vector<int>> _tilesBase;
	std::vector<std::vector<int>> _tiles;

	const std::string* _fileMap;

	void init();
	void saveMap();
	void loadMap();
	void loadMapBase();
};