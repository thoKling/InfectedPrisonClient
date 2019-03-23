#pragma once
#include "DrawableEntity.h"
#include "LTBL2/lighting/LightPointEmission.h"

class Item;

class Character : public DrawableEntity
{
public:
	Character();
	~Character();

	/* Proc�dure qui r�cup�re et traite les entr�es clavier du joueur */
	void handleInputs(const sf::Event& event);

	/* Proc�dure qui d�place le personnage */
	void mv();

	void receiveHit(const sf::Vector2f& hitterPosition);
	void pickItem();

	void dropItem();

	void update(const sf::Vector2f& mousePos);

private:
	// La vitesse de d�placement du personnage
	double _velocity = 5;
	bool _beingHit = false;
	unsigned int _lives = 3;
	bool _alive = true;
	void die();

	// Boolean indiquant si oui ou non le joueur est en train de frapper
	bool _isPunching;
	// Boolean indiquant si oui ou non le joueur peut frapper
	bool _canPunch;
	// nombre de secondes pour mettre un coup de poing
	const float _punchingSpeed;
	// nombre de tick depuis la derni�re update du punch( 1tick = 0.06s)
	int _tickSincePunchingUpdate;

	std::shared_ptr<ltbl::LightPointEmission> light;
	sf::Texture pointLightTexture;

	Item* _currentItem;

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

