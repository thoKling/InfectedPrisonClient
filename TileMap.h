#pragma once

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles, unsigned int width, unsigned int height);
	const std::vector<std::vector<int>>& getTiles() const;
	int getTileNumber(sf::Vector2i tilePos);
	bool isObstacle(sf::Vector2i tilePos);
	TileMap();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<std::vector<int>> _tiles;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};