#include "PlayerController.h"

#include "Application.h"
#include "InventoryView.h"
#include "World.h"
#include "HUD.h"
#include "Player.h"



PlayerController::PlayerController() :
	_inventory(new Inventory()),
	//_player(new Player(_inventory)),
	_isInventoryOpen(false)
{
	_player = new Player(_inventory);
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

	if (_isInventoryOpen) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			_inventory->getInventoryView()->handleInputs(event);
	}
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (_inventory->getCurrentItem() != nullptr)
				_inventory->getCurrentItem()->use(_player);

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
	if (_inventory->getCurrentItem() != nullptr) {
		HUD::setAmmo(_inventory->getCurrentItem()->getAmmo());
	}
	else
		HUD::setAmmo(0);
	HUD::setLives(_lives);

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
