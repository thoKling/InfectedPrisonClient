#pragma once
#include "DrawableEntity.h"
#include "LTBL2/lighting/LightPointEmission.h"

class Item;

class Player : public DrawableEntity
{
public:
	// Apparence du personnage
	enum Showing {
		Stand, Armed, Reloading,
	};

	Player(std::string name);
	~Player();

	void receiveHit(const sf::Vector2f& hitterPosition);

	void update();

	// Getters and Setters
	void setShowing(Showing showing);
	Showing getShowing();
	std::string getName();

	unsigned int getLives();
	bool getHitState() const;
	//void setUpState(bool state);
	double getVelocity();

private:
	std::string _name;
	Showing _showing;

	// La vitesse de déplacement du personnage
	double _velocity = 5;


	std::shared_ptr<ltbl::LightPointEmission> light;
	sf::Texture pointLightTexture;

	bool _beingHit = false;

	unsigned int _lives = 3;
};

