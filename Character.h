#pragma once
#include "DrawableEntity.h"
#include "Weapon.h"

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
	void fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager);
	void reload();
	void receiveWeapon();
	void throwWeapon();

	void update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager);

	void draw();

private:
	// La vitesse de d�placement du personnage
	double _velocity = 3;
	bool _beingHit = false;

	// Boolean indiquant si oui ou non le joueur est en train de frapper
	bool _isPunching;
	// Boolean indiquant si oui ou non le joueur peut frapper
	bool _canPunch;
	// nombre de secondes pour mettre un coup de poing
	const float _punchingSpeed;
	// nombre de tick depuis la derni�re update du punch( 1tick = 0.06s)
	int _tickSincePunchingUpdate;

	TileMap* _map;

	Weapon* _weapon;

	/* Les "interrupteurs de d�placement".
	True: les d�placements ont lieu,
	False: il n'y a pas de d�placements */
	bool _dIsHeld = false;
	bool _qIsHeld = false;
	bool _sIsHeld = false;
	bool _upIsHeld = false;

	// Interrupteur de tir
	bool _fire = false;
};

