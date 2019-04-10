#pragma once

#include "Inventory.h"

class InventoryView;
class Player;

class PlayerController
{
public:
	PlayerController(Player* player);
	~PlayerController();

	/* Procédure qui récupère et traite les entrées clavier du joueur */
	void handleInputs(const sf::Event& event);

	void receiveHit(const sf::Vector2f& hitterPosition);

	void update(const sf::Vector2f& mousePos);

	Player* getPlayer() const;

	// Procédure qui dessine les personnages
	void manageDrawCharacter(sf::RenderWindow& window);

	// Procédure qui dessine les inventaires
	void manageDrawInventory(sf::RenderWindow& window);

private:

	// L'inventaire est il ouvert?
	bool _isInventoryOpen;

	Player* _player;

	Inventory _inventory;
	InventoryView* _inventoryView;
	
	unsigned int _lives = 3;
	bool _alive = true;
	void die();
	void reload();

	void pickItem();
	void dropItem();
};

