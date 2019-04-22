#include "Region.h"

#include "Weapon.h"
#include "Utils.h"
#include "Ammo.h"
#include "Key.h"
#include "ZombiesManager.h"
#include "SocketManager.h"

#include <iostream>
#include <fstream>

Region::Region(const std::string& fileMap):
	_fileMap(&fileMap)
{
	loadMap();
	init();
}

Region::Region(std::vector<std::vector<int>>& tiles):
	_tiles(tiles)
{
	init();
}

void Region::init() {
	loadMapBase();

	// on crée la tilemap avec le niveau précédemment défini
	if (!_map.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), _tiles))
		throw std::string("Impossible de charger la map");

	// Création d'un zombie
	if (!SocketManager::isOnline()) {
		ZombiesManager::createZombie(sf::Vector2f(1576, 810));
		DroppedItem* temp = new DroppedItem(new Weapon());
		temp->setPosition({ 856, 870 });
		_items.emplace_back(temp);
	}
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
	window.draw(_mapBase);
	window.draw(_map);
	// On dessine les items
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		window.draw(**it);
	}
}

void Region::update()
{
	if (SocketManager::isOnline())
		return;
	++_ticks;
	//create ammo
	if (_ticks % 600 == 0) {
		Item* tempItem = new Ammo(WeaponType::Gun);
		tempItem->setStack(4);
		DroppedItem* temp2 = new DroppedItem(tempItem);
		int x;
		int y;
		int place = rand()%4;
		std::cout << place << std::endl;
		switch (place) {
			case 0: 
				x = 856;
				y = 870;
				break;
			case 1: 
				x = 1156;
				y = 600;
				break;
			case 2: 
				x = 1956;
				y = 600;
				break;
			case 3: 
				x = 856;
				y = 870;
				break;
		}
		temp2->setPosition(sf::Vector2f( x + rand()%30, y + rand()%30));
		_items.emplace_back(temp2);
	}
	if((_ticks + 30)%600 == 0)
		ZombiesManager::createZombie(sf::Vector2f(2560 + (int)(rand()%100), 1600 + (int)(rand()%100)));
}

void Region::saveMap() {
	std::ofstream outfile;
	outfile.open(*_fileMap);

	for (int i = 0; i < _tiles.size(); i++) {
		for (int j = 0; j < _tiles[0].size(); j++) {
			outfile << _tiles[i][j] << ",";
		}
		if(i!= _tiles.size())
			outfile << "\n";
	}
}

void Region::loadMap() {
	std::ifstream infile;
	infile.open(*_fileMap);
	if (!infile)
	{
		std::cout << "There was an error opening the file.\n";
	}

	char ch;
	int currentNumber = 0;
	std::vector<int> temp;

	while (!infile.eof()) {
		infile.get(ch);

		if (ch == ',') {
			temp.push_back(currentNumber);
			currentNumber = 0;
		}
		else if (ch == '\n') {
			_tiles.push_back(temp);
			temp.clear();
		}
		else {
			int ia = ch - '0';
			currentNumber = currentNumber * 10 + ia;
		}
	}
	_tiles.push_back(temp);
}

void Region::loadMapBase() {
	std::ifstream infile;
	infile.open("Chunks/base.txt");
	if (!infile)
	{
		std::cout << "There was an error opening the file.\n";
	}

	char ch;
	int currentNumber = 0;
	std::vector<int> temp;

	while (!infile.eof()) {
		infile.get(ch);

		if (ch == ',') {
			temp.push_back(currentNumber);
			currentNumber = 0;
		}
		else if (ch == '\n') {
			_tilesBase.push_back(temp);
			temp.clear();
		}
		else {
			int ia = ch - '0';
			currentNumber = currentNumber * 10 + ia;
		}
	}
	_tilesBase.push_back(temp);

	// on crée la tilemap avec le niveau précédemment défini
	if (!_mapBase.load("Ressources/Tilesheet/tileset.png", sf::Vector2u(64, 64), _tilesBase))
		throw std::string("Impossible de charger la map");
}

// Renvoit l'item le plus proche de la position dans une certaine portée et le supprime de la région, nullptr si il n'y en a pas
DroppedItem* Region::getDroppedItemInRect(const sf::FloatRect& rect) {
	DroppedItem* res = nullptr;
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		if ((*it)->getGlobalBounds().intersects(rect)) {
			res = *it;
			break;
		}
	}
	_items.remove(res);
	return res;
}

void Region::dropItem(Item * item, const sf::Vector2f & position)
{
	if(!SocketManager::isOnline()) {
		DroppedItem* temp = new DroppedItem(item);
		temp->setPosition(position);
		_items.emplace_back(temp);
	}
	else {
		sf::Packet packet;
		packet << SocketManager::PacketType::CreateItem << *item << position;
		SocketManager::send(packet);
	}
}

void Region::addItem(Item * item, const sf::Vector2f & position)
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

void Region::deleteItem(Item * item, const sf::Vector2f pos)
{
	auto toDelete = _items.begin();
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it)->getItem()->getType() == item->getType()
			&& (*it)->getItem()->getStack() == item->getStack()
			&& (*it)->getPosition() == pos) {
			toDelete = it;
		}
	}
	_items.erase(toDelete);
}

bool Region::isObstacle(sf::Vector2i tilePos)
{
	return !((getTileNumber(tilePos) == 10) || (getTileNumber(tilePos) == 319));
}