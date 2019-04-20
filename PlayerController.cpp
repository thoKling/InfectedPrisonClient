#include "PlayerController.h"

#include "Application.h"
#include "InventoryView.h"
#include "World.h"
#include "HUD.h"
#include "Player.h"
#include "SocketManager.h"


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
void PlayerController::handleInputs(const sf::Event& event)
{
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
		_inventory->getInventoryView()->handleInputs(event);
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

void PlayerController::update(const sf::Vector2f& mousePos)
{
	_player->orientate(mousePos);
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
	_inventory->getInventoryView()->update(mousePos);
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
	Item* item = World::getInstance()->getItemInRect(_player->getGlobalBounds());

	if (item != nullptr) {
		_inventory->AddItem(item);
		if (item->getWeaponType() != WeaponType::NaW)
			_inventory->setCurrentItem(item);
	}
}

void PlayerController::dropItem() {
	if (_inventory->getCurrentItem() != nullptr) {
		World::getInstance()->dropItem(_inventory->getCurrentItem(), _player->getPosition());
		_inventory->dropItem(_inventory->getCurrentItem());
		_inventory->setCurrentItem(nullptr);
	}
}

void PlayerController::reload()
{
	if (_inventory->getCurrentItem() != nullptr) {
		WeaponType typeW = _inventory->getCurrentItem()->getWeaponType();
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
