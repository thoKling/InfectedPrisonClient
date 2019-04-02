#include "Region.h"

#include "Weapon.h"
#include "Utils.h"
#include "Ammo.h"

#include <iostream>

Region::Region(const std::vector<std::vector<int>>& tiles)
{
	// on crée la tilemap avec le niveau précédemment défini
	if (!_map.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), tiles, 32, 16))
		throw std::string("Impossible de charger la map");
	_tiles = tiles;
	DroppedItem* temp = new DroppedItem(new Weapon());
	temp->setPosition({ 50, 50 });
	_items.emplace_back(temp);

	Item* tempItem = new Ammo(WeaponType::Gun);
	tempItem->setStack(18);
	DroppedItem* temp2 = new DroppedItem(tempItem);
	temp2->setPosition({100,100});
	_items.emplace_back(temp2);
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