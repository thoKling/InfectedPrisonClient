#pragma once

#include <SFML/Graphics.hpp>
#include "LTBL2/lighting/LightSystem.h"

class ZombiesManager;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(ltbl::LightSystem* ls, const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles, unsigned int width, unsigned int height);
	const std::vector<std::vector<int>>& getTiles() const;
	int getTileNumber(sf::Vector2i tilePos);
	ZombiesManager* getZombiesManager();
	bool isObstacle(sf::Vector2i tilePos);
	TileMap(ZombiesManager* zombiesManager);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<std::vector<int>> _tiles;

	ZombiesManager* _zombiesManager;
	sf::VertexArray _vertices;
	sf::Texture _tileset;
};