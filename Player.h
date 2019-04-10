#pragma once
#include "DrawableEntity.h"
#include "Inventory.h"
#include "LTBL2/lighting/LightPointEmission.h"

class Item;

class Player : public DrawableEntity
{
public:
	Player(Inventory* inventory);
	~Player();

	/* Proc�dure qui d�place le personnage */
	void mv();

	void receiveHit(const sf::Vector2f& hitterPosition);

	void update(const sf::Vector2f& mousePos);

	// Getters and Setters
	Inventory* getInventory() const;

	//bool getDState() const;
	void setDState(bool state);
	//bool getQState() const;
	void setQState(bool state);
	//bool getSState() const;
	void setSState(bool state);
	//bool getUpState() const;
	void setUpState(bool state);
	bool getHitState() const;
	//void setUpState(bool state);

private:

	Inventory* _inventory;

	// La vitesse de d�placement du personnage
	double _velocity = 5;

	/* Les "interrupteurs de d�placement".
	True: les d�placements ont lieu,
	False: il n'y a pas de d�placements */
	bool _dIsHeld = false;
	bool _qIsHeld = false;
	bool _sIsHeld = false;
	bool _upIsHeld = false;

	std::shared_ptr<ltbl::LightPointEmission> light;
	sf::Texture pointLightTexture;

	bool _beingHit = false;

	// Interrupteur de tir
	bool _fire = false;
};

