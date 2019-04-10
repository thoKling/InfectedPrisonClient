#include "PlayerController.h"

#include "Application.h"
#include "InventoryView.h"
#include "World.h"
#include "HUD.h"
#include "Player.h"



PlayerController::PlayerController(Player* player):
	_inventoryView(new InventoryView(&_inventory)),
	_isInventoryOpen(false),
	_player(player)
{
}


PlayerController::~PlayerController()
{
	delete _inventoryView;
	delete _player;
}

/** Récupération et traitement des entrées clavier du joueur **/
void PlayerController::handleInputs(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		_isInventoryOpen = true;
		_player->setDState(false);
		_player->setQState(false);
		_player->setSState(false);
		_player->setUpState(false);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		_isInventoryOpen = false;


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player->setDState(false);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_player->setQState(false);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_player->setSState(false);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_player->setUpState(false);

	if (!_isInventoryOpen) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (_player->getCurrentItem() != nullptr)
				_player->getCurrentItem()->use(_player);

		//if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		//	_fire = false;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_player->setDState(true);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			_player->setQState(true);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_player->setSState(true);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			_player->setUpState(true);

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

void PlayerController::update(const sf::Vector2f& mousePos)
{
	_player->update(mousePos);
	if (_player->getCurrentItem() != nullptr) {
		HUD::setAmmo(_player->getCurrentItem()->getAmmo());
	}
	else
		HUD::setAmmo(0);
	HUD::setLives(_lives);

	_inventoryView->update(&_inventory);
}

// on draw le personnage
void PlayerController::manageDrawCharacter(sf::RenderWindow& window) {
	window.draw(*_player);
}

// on draw l'inventaire
void PlayerController::manageDrawInventory(sf::RenderWindow& window) {
	if (_isInventoryOpen) {
		window.draw(*_inventoryView);
	}
}

void PlayerController::receiveHit(const sf::Vector2f& hitterPosition)
{
	if (!_player->getHitState() && _alive) {
		_player->receiveHit(hitterPosition);
		--_lives;
		if (!_lives)
			die();
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
		_inventory.AddItem(item);
		if (item->getWeaponType() != WeaponType::NaW)
			_player->setCurrentItem(item);
	}
}

void PlayerController::dropItem() {
	if (_player->getCurrentItem() != nullptr) {
		World::getInstance()->dropItem(_player->getCurrentItem(), _player->getPosition());
		_inventory.dropItem(_player->getCurrentItem());
		_player->setCurrentItem(nullptr);
	}
}

void PlayerController::reload()
{
	if (_player->getCurrentItem() != nullptr) {
		WeaponType typeW = _player->getCurrentItem()->getWeaponType();
		unsigned int usedAmmos = _player->getCurrentItem()->reload(_inventory.getAmmos(typeW));
		_inventory.setAmmos(typeW, usedAmmos);
	}
}

Player* PlayerController::getPlayer() const {
	return _player;
}
