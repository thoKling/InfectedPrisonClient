#pragma once

#include <SFML/Graphics.hpp>
#include "LTBL2/lighting/LightSystem.h"

class ZombiesManager;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles, unsigned int width, unsigned int height);
	TileMap();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};