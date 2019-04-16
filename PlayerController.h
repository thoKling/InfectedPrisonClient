#pragma once

#include "Inventory.h"

class Player;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	/* Proc�dure qui r�cup�re et traite les entr�es clavier du joueur */
	void handleInputs(const sf::Event& event);

	void receiveHit(const sf::Vector2f& hitterPosition);

	void update(const sf::Vector2f& mousePos);

	// Proc�dure qui dessine les personnages
	void manageDrawCharacter(sf::RenderWindow& window);

	// Proc�dure qui dessine les inventaires
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

