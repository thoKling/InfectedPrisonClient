#include "MapUtils.h"
#include "World.h"

#include <iostream>

std::list<sf::Vector2i> MapUtils::getPath(const sf::Vector2i& startCell, const sf::Vector2i& endCell)
{
	// Initialisation
	bool found = false;

	const std::vector<std::vector<int>>& tiles = World::getInstance()->getTiles();

	const unsigned int width = tiles[0].size();
	const unsigned int height = tiles.size();

	const sf::Vector2i obstacle = sf::Vector2i(-999,-999);

	const unsigned int obstacle_tileNumber = 10;

	sf::Vector2i* _parentOfCell = new sf::Vector2i[width*height];

	for (size_t x = 0; x < width; x++)
		for (size_t y = 0; y < height; y++) {
			if (tiles[y][x] != obstacle_tileNumber)
				_parentOfCell[x + width * y] = obstacle; // Obstacles
			else 
				_parentOfCell[x + width * y].x = -1;
		}

	_parentOfCell[startCell.x + width * startCell.y] = obstacle;

	std::vector<sf::Vector2i> nextCells;
	nextCells.push_back(startCell);

	// Parcours
	while (nextCells.size() != 0 && !found)
	{			
		std::vector<sf::Vector2i> tempNextCells;
		for (size_t i = 0; i < nextCells.size(); i++)
		{
			sf::Vector2i nextCell = nextCells[i];

			sf::Vector2i adjCells[8] = {
				sf::Vector2i(nextCell.x - 1, nextCell.y), // a gauche
				sf::Vector2i(nextCell.x, nextCell.y - 1), // en haut
				sf::Vector2i(nextCell.x + 1, nextCell.y), // a droite
				sf::Vector2i(nextCell.x, nextCell.y + 1), // en bas
				// les diagonales
				sf::Vector2i(nextCell.x - 1, nextCell.y - 1), // en haut a gauche
				sf::Vector2i(nextCell.x + 1, nextCell.y - 1), // en haut a droite
				sf::Vector2i(nextCell.x + 1, nextCell.y + 1), // en bas a droite
				sf::Vector2i(nextCell.x - 1, nextCell.y + 1), // en bas a gauche
			};
			int diag[4] = {0,0,0,0};

			sf::Vector2i* cell;

			for (size_t j = 0; j < 4; j++)
			{
				cell = &adjCells[j];
				if (_parentOfCell[cell->x + width * cell->y].x == -1)
				{
					diag[j] = 1;
					_parentOfCell[cell->x + width * cell->y] = nextCell;

					tempNextCells.push_back(*cell);
					if (*cell == endCell)
					{
						found = true;
						break;
					}
				}
				else if (_parentOfCell[cell->x + width * cell->y] != obstacle)
					diag[j] = 1;
			}
			sf::Vector2i* cellDiag;
			// On test les diagonales
			for (size_t j = 4; j < 8; j++)
			{
				cellDiag = &adjCells[j];
				int temp = (j-4)+1 == 4 ? 0 : j-4;

				if (_parentOfCell[cellDiag->x + width * cellDiag->y].x == -1 && diag[j-4] == 1 && diag[temp] == 1)
				{
					_parentOfCell[cellDiag->x + width * cellDiag->y] = nextCell;

					tempNextCells.insert(tempNextCells.begin(),*cellDiag);

					if (*cellDiag == endCell)
					{
						found = true;
						break;
					}
				}
			}
		}			
		nextCells = tempNextCells;
		tempNextCells.clear();
	}

	// Résultat (recherche du chemin)
	std::list<sf::Vector2i> path = std::list<sf::Vector2i>();

	sf::Vector2i currentCell = endCell;
	while (currentCell != startCell && found)
	{
		path.push_front(currentCell);
		currentCell = _parentOfCell[currentCell.x + width * currentCell.y];
	}

	delete _parentOfCell;

	return path;
}


// transforme une position relative à la fenetre en coordonnées de tiles
sf::Vector2i MapUtils::transformInTilesPos(const sf::Vector2f& pos)
{
	return sf::Vector2i((int)(pos.x) / TILESIZE, (int)(pos.y) / TILESIZE);
}
