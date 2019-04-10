#pragma once

#include "Inventory.h"

class Player;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	/* Procédure qui récupère et traite les entrées clavier du joueur */
	void handleInputs(const sf::Event& event);

	void receiveHit(const sf::Vector2f& hitterPosition);

	void update(const sf::Vector2f& mousePos);

	// Procédure qui dessine les personnages
	void manageDrawCharacter(sf::RenderWindow& window);

	// Procédure qui dessine les inventaires
	void manageDrawInventory(sf::RenderWindow& window);

	Player* getPlayer() const;
	Inventory* getInventory() const;

private:

	// L'inventaire est il ouvert?
	bool _isInventoryOpen;

	Player* _player;

	Inventory* _inventory;
	
	unsigned int _lives = 3;
	bool _alive = true;
	void die();
	void reload();

	void pickItem();
	void dropItem();
};

