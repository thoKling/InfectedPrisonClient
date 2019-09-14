#include "PlayerController.h"

#include "Application.h"
#include "InventoryView.h"
#include "World.h"
#include "HUD.h"
#include "Player.h"
#include "SocketManager.h"

#include <iostream>


PlayerController::PlayerController() :
	_inventory(new Inventory()),
	_isInventoryOpen(false)
{
}


PlayerController::~PlayerController()
{
	delete _player;
	delete _inventory;
}

/** Récupération et traitement des entrées clavier du joueur **/
void PlayerController::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	_player->orientate(mousePos);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		_isInventoryOpen = true;
		_dIsHeld = false;
		_qIsHeld = false;
		_sIsHeld = false;
		_upIsHeld = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		_isInventoryOpen = false;


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_dIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_qIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_sIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_upIsHeld = false;

	if (_isInventoryOpen) {
		_inventory->getInventoryView()->handleInputs(mousePixelPos, mousePos);
	}
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (_inventory->getCurrentItem() != nullptr)
				_inventory->getCurrentItem()->use(_player);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_dIsHeld = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			_qIsHeld = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_sIsHeld = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			_upIsHeld = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			reload();

		if (event.type == sf::Event::KeyReleased)
			switch (event.key.code) {
			case sf::Keyboard::E:
				pickItem();
				break;
			case sf::Keyboard::F:
				dropItem();
				break;
			}
	}
}
void PlayerController::movePlayer()
{
	double x = 0, y = 0;

	if (_dIsHeld)
		x += _player->getVelocity();

	if (_qIsHeld)
		x += -_player->getVelocity();

	if (_sIsHeld)
		y += _player->getVelocity();

	if (_upIsHeld)
		y += -_player->getVelocity();

	// Surtout utile pour les diagonales
	sf::Vector2f unitVec = Utils::getVecUnit(sf::Vector2f(0, 0), sf::Vector2f(x, y));
	x *= std::abs(unitVec.x);
	y *= std::abs(unitVec.y);

	// Déplacement en x
	_player->move(x, 0);
	if (_player->isInObstacle())
		_player->move(-x, 0);

	// Déplacement en y
	_player->move(0, y);
	if (_player->isInObstacle())
		_player->move(0, -y);
}

void PlayerController::update()
{
	_player->update();

	movePlayer();

	if (SocketManager::isOnline()) {
		sf::Packet packet;
		packet << SocketManager::PacketType::PlayerPos << _player->getPosition() << _player->getRotation() << (int)_player->getShowing();
		SocketManager::send(packet);
	}

	if (_inventory->getCurrentItem() != nullptr) {
		_inventory->getCurrentItem()->update();
		if (_inventory->getCurrentItem()->isReloading())
			_player->setShowing(Player::Showing::Reloading);
		else
			_player->setShowing(Player::Showing::Armed);
		HUD::setAmmo(_inventory->getCurrentItem()->getAmmo());
	}
	else {
		HUD::setAmmo(0);
		_player->setShowing(Player::Showing::Stand);
	}
	if (!_player->getLives())
		die();
	HUD::setLives(_player->getLives());
	_inventory->getInventoryView()->update();

	manageDroppedItems();

}

void PlayerController::attach(Player * player)
{
	_player = player;
}

// on draw le personnage
void PlayerController::manageDrawCharacter(sf::RenderWindow& window) {
	window.draw(*_player);
}

// on draw l'inventaire
void PlayerController::manageDrawInventory(sf::RenderWindow& window) {
	if (_isInventoryOpen) {
		window.draw(*_inventory->getInventoryView());
	}
}

void PlayerController::die()
{
	_alive = false;
	World::getInstance()->gameOver();
}

void PlayerController::pickItem() {
	DroppedItem* droppedItem = World::getInstance()->getItemInRect(_player->getGlobalBounds());

	if (droppedItem != nullptr) {
		Item* item = droppedItem->getItem();
		if (_inventory->getCurrentItem() == nullptr && item->getItemType() == ItemType::Gun)
			_inventory->setCurrentItem(item);
		_inventory->AddItem(item);
		if (SocketManager::isOnline()) {
			sf::Packet packet;
			packet << SocketManager::PacketType::DeleteItem << *item << droppedItem->getCorners()[0];
			SocketManager::send(packet);
		}
	}
	delete(droppedItem);
}

void PlayerController::dropItem() {
	if (_inventory->getCurrentItem() != nullptr) {
		World::getInstance()->dropItem(_inventory->getCurrentItem(), _player->getPosition());
		_inventory->dropItem(_inventory->getCurrentItem());
		_inventory->setCurrentItem(nullptr);
	}
}

void PlayerController::manageDroppedItems() {
	std::vector<Item*> itemsDroppedFromInventory = _inventory->getDroppedItems();
	
	Region* region = World::getInstance()->getCurrentRegion();
	for (auto &item : itemsDroppedFromInventory) // access by reference to avoid copying
	{
		region->dropItem(item, _player->getPosition());
	}
	_inventory->deleteDroppedItems();
}

void PlayerController::reload()
{
	if (_inventory->getCurrentItem() != nullptr) {
		ItemType typeW = _inventory->getCurrentItem()->getItemType();
		unsigned int usedAmmos = _inventory->getCurrentItem()->reload(_inventory->getAmmos(typeW));
		_inventory->setAmmos(typeW, usedAmmos);
	}
}

Player* PlayerController::getPlayer() const {
	return _player;
}

Inventory* PlayerController::getInventory() const {
	return _inventory;
}
