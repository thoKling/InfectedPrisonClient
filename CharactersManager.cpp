#include "CharactersManager.h"

#include <iostream>

#include "TileMap.h"
#include "LTBL2/lighting/LightSystem.h"

CharactersManager::CharactersManager(TileMap* map, ltbl::LightSystem* ls) : _map(map), _nextId(0), _ls(ls)
{
}


// on désalloue la mémoire utilisée pour stocker les personnages
CharactersManager::~CharactersManager()
{
	for (auto it = _characters.begin(); it != _characters.end(); ++it)
	{
		delete it->second;
	}
}


// créer un nouveau personnage et renvoit l'id de ce dernier
unsigned int CharactersManager::createCharacter(const sf::Vector2f& pos) {
	_characters[_nextId] = new Character(_map, _ls);
	_characters[_nextId]->setPosition(pos);
	_nextId++;
	return _nextId - 1;
}

// renvoit la liste des personnages (une copie ?) 
std::map<unsigned int, Character*> CharactersManager::getCharacters()
{
	return _characters;
}


// on draw chaque personnage
void CharactersManager::manageDraw(sf::RenderWindow& window) {
	for (auto it = _characters.begin(); it != _characters.end(); ++it)
	{
		window.draw(*it->second);
	}
}


// Récupération des entrées clavier liées aux personnages
void CharactersManager::handleInputs(const sf::Event& event)
{
	_characters[0]->handleInputs(event);
}

// Mise à jour du comportement des personnages
void CharactersManager::update(const sf::Vector2f& mousePos)
{
	_characters[0]->update(mousePos);
}