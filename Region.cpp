#include "Region.h"

#include "Weapon.h"
#include "Utils.h"
#include "Ammo.h"
#include "Key.h"
#include "ZombiesManager.h"

#include <iostream>

Region::Region(const std::vector<std::vector<int>>& tiles)
{
	// on crée la tilemap avec le niveau précédemment défini
	if (!_map.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), tiles, 32, 16))
		throw std::string("Impossible de charger la map");
	_tiles = tiles;
	DroppedItem* temp = new DroppedItem(new Weapon());
	temp->setPosition({ 150, 150 });
	_items.emplace_back(temp);

	Item* tempItem = new Ammo(WeaponType::Gun);
	tempItem->setStack(18);
	DroppedItem* temp2 = new DroppedItem(tempItem);
	temp2->setPosition({500,300});
	//_items.emplace_back(temp2);
}


Region::~Region()
{
	// On désalloue la mémoire des items
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		delete(*it);
	}
}

void Region::manageDraw(sf::RenderWindow & window)
{
	// On dessine la map
	window.draw(_map);
	// On dessine les items
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		window.draw(**it);
	}
}

void Region::update()
{
	++_ticks;
	if (_ticks % 600 == 0) {
		Item* tempItem = new Ammo(WeaponType::Gun);
		tempItem->setStack(4);
		DroppedItem* temp2 = new DroppedItem(tempItem);
		
		/*int tempX, tempY;
		do {
			tempX = rand() % (_tiles[0].size() * 64);
			tempY = rand() % (_tiles.size() * 64);
		} while (isObstacle(sf::Vector2i((int)tempX, (int)tempY)));

		temp2->setPosition(sf::Vector2f((int)tempX, (int)tempY));*/

		temp2->setPosition(sf::Vector2f( 500 + (int)(rand()% 50),300 + (int)(rand()%50) ));
		_items.emplace_back(temp2);

		Item* tempKey = new Key();
		tempKey->setStack(1);
		DroppedItem* tempKey2 = new DroppedItem(tempKey);
		tempKey2->setPosition(sf::Vector2f(150, 150));
		_items.emplace_back(tempKey2);
	}
	if((_ticks + 30)%600 == 0)
		ZombiesManager::createZombie(sf::Vector2f(800 + (int)(rand()%100), 500 + (int)(rand()%100)));
}

// Renvoit l'item le plus proche de la position dans une certaine portée et le supprime de la région, nullptr si il n'y en a pas
Item* Region::getItemInRect(const sf::FloatRect& rect) {
	DroppedItem* res = nullptr;

	for (auto it = _items.begin(); it != _items.end(); ++it) {
		if ((*it)->getGlobalBounds().intersects(rect)) {
			res = *it;
			break;
		}
	}
	if (res == nullptr)
		return nullptr;

	Item* itemRes = res->getItem();
	_items.remove(res);
	delete(res);
	return itemRes;
}

void Region::dropItem(Item * item, const sf::Vector2f & position)
{
	DroppedItem* temp = new DroppedItem(item);
	temp->setPosition(position);
	_items.emplace_back(temp);
}

///
/// Partie utils de la region
///

const std::vector<std::vector<int>>& Region::getTiles() const
{
	return _tiles;
}

// Renvoit le numéro de tile
int Region::getTileNumber(sf::Vector2i tilePos)
{
	// si on demande une position en dehors de la map
	if (tilePos.x >= _tiles[0].size() || tilePos.y >= _tiles.size()) {
		std::cout << "Position demandée en dehors de la région" << std::endl;
		return -1;
	}
	return _tiles[tilePos.y][tilePos.x];
}

bool Region::isObstacle(sf::Vector2i tilePos)
{
	return getTileNumber(tilePos) == 41;
}