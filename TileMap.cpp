#include "TileMap.h"

#include <iostream>

TileMap::TileMap() {

}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles, unsigned int width, unsigned int height) {
	_tiles = tiles;
	// on charge la texture du tileset
	if (!_tileset.loadFromFile(tileset))
		return false;

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// on récupère le numéro de tuile courant
			int tileNumber = tiles[j][i];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &_vertices[(i + j * width) * 4];

			// on définit ses quatre coins
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

std::vector<std::vector<int>> TileMap::getTiles() const
{
	return _tiles;
}

// Renvoit le numéro de tile
int TileMap::getTileNumber(sf::Vector2i tilePos)
{
	// si on demande une position en dehors de la map
	if (tilePos.x >= _tiles[0].size() || tilePos.y >= _tiles.size()) {
		std::cout << "Position demandée en dehors de la map" << std::endl;
		return -1;
	}
	return _tiles[tilePos.y][tilePos.x];
}

bool TileMap::isObstacle(sf::Vector2i tilePos)
{
	return getTileNumber(tilePos) == 41;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = &_tileset;

	// et on dessine enfin le tableau de vertex
	target.draw(_vertices, states);
}