#pragma once
#include "DrawableEntity.h"

class TileMap;
class ProjectilesManager;
class AudioManager;

class Character : public DrawableEntity
{
public:
	Character(TileMap* map);
	~Character();

	/* Proc�dure qui r�cup�re et traite les entr�es clavier du joueur */
	void handleInputs(const sf::Event& event);


	/* Proc�dure qui d�place le personnage */
	void mv();

	void receiveHit(const sf::Vector2f& hitterPosition);
	void fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager);

	void update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager);

private:
	// La vitesse de d�placement du personnage
	double _velocity = 3;
	bool _beingHit = false;

	TileMap* _map;

	/* Les "interrupteurs de d�placement".
	True: les d�placements ont lieu,
	False: il n'y a pas de d�placements */
	bool _rightIsHeld = false;
	bool _leftIsHeld = false;
	bool _downIsHeld = false;
	bool _upIsHeld = false;

	// Interrupteur de tir
	bool _fire = false;
};

