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
	void receiveHit(sf::Vector2f hitterPosition);
	bool isDead();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool _beingHit = false;

	unsigned int _lifes = 3;

	void myMove();

	float _velocity;

	TileMap* _map;
	CharactersManager* _charManager;
	
	sf::Vector2f _target;
	sf::Vector2i _lastTileTarget;
};

