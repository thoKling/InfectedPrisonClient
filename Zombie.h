#pragma once
#include "DrawableEntity.h"

class TileMap;
class CharactersManager;

class Zombie : public DrawableEntity
{
public:
	Zombie(TileMap* map, CharactersManager* charManager);
	~Zombie();

	void update();
	sf::Vector2i getPositionTiles();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void myMove();

	float _velocity;

	TileMap* _map;
	CharactersManager* _charManager;
	
	sf::Vector2f _target;
	sf::Vector2i _lastTileTarget;
};

