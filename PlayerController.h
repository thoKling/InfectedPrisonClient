#pragma once

#include "Inventory.h"

class Player;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	/* Procédure qui récupère et traite les entrées clavier du joueur */
	void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);

	void movePlayer();

	void update();

	void attach(Player* player);

	// Procédure qui dessine les personnages
	void manageDrawCharacter(sf::RenderWindow& window);

	// Procédure qui dessine les inventaires
	void manageDrawInventory(sf::RenderWindow& window);

	Player* getPlayer() const;
	Inventory* getInventory() const;

private:
	/* Les "interrupteurs de déplacement".
	True: les déplacements ont lieu,
	False: il n'y a pas de déplacements */
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

