#pragma once

#include "Inventory.h"

class Player;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	/* Proc�dure qui r�cup�re et traite les entr�es clavier du joueur */
	void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);

	void movePlayer();

	void update();

	void attach(Player* player);

	// Proc�dure qui dessine les personnages
	void manageDrawCharacter(sf::RenderWindow& window);

	// Proc�dure qui dessine les inventaires
	void manageDrawInventory(sf::RenderWindow& window);

	Player* getPlayer() const;
	Inventory* getInventory() const;

private:
	/* Les "interrupteurs de d�placement".
	True: les d�placements ont lieu,
	False: il n'y a pas de d�placements */
	bool _dIsHeld = false;
	bool _qIsHeld = false;
	bool _sIsHeld = false;
	bool _upIsHeld = false;
	// L'inventaire est il ouvert?
	bool _isInventoryOpen;

	Player* _player;

	Inventory* _inventory;

	bool _alive = true;
	void die();
	void reload();

	void pickItem();
	void dropItem();

	void manageDroppedItems();
};

