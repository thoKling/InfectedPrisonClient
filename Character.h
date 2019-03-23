#pragma once
#include "DrawableEntity.h"
#include "LTBL2/lighting/LightPointEmission.h"

class Item;

class Character : public DrawableEntity
{
public:
	Character();
	~Character();

	/* Procédure qui récupère et traite les entrées clavier du joueur */
	void handleInputs(const sf::Event& event);

	/* Procédure qui déplace le personnage */
	void mv();

	void receiveHit(const sf::Vector2f& hitterPosition);
	void pickItem();

	void dropItem();

	void update(const sf::Vector2f& mousePos);

private:
	// La vitesse de déplacement du personnage
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
	// nombre de tick depuis la dernière update du punch( 1tick = 0.06s)
	int _tickSincePunchingUpdate;

	std::shared_ptr<ltbl::LightPointEmission> light;
	sf::Texture pointLightTexture;

	Item* _currentItem;

	/* Les "interrupteurs de déplacement".
	True: les déplacements ont lieu,
	False: il n'y a pas de déplacements */
	bool _dIsHeld = false;
	bool _qIsHeld = false;
	bool _sIsHeld = false;
	bool _upIsHeld = false;

	// Interrupteur de tir
	bool _fire = false;
};

