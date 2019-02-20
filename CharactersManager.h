#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"

class TileMap;

class CharactersManager
{
public:
	CharactersManager(TileMap* map);
	~CharactersManager();

	// M�thode qui permet de cr�er un nouveau personnage
	unsigned int createCharacter(const sf::Vector2f& pos);

	// M�thode qui renvoit la liste des personnages
	std::map<unsigned int, Character*> getCharacters();

	// Proc�dure qui dessine les personnages
	void manageDraw(sf::RenderWindow& window);

	// Proc�dure qui r�cup�re et traite les entr�es clavier li�es aux personnages
	void handleInputs(const sf::Event& event);

	// Proc�dure qui met � jour le comportement des personnages
	void update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager);

private:
	// Liste des personnages
	std::map<unsigned int, Character*> _characters;

	TileMap* _map;

	// identifiant suivant servant � la cr�ation d'un nouveau personnage
	unsigned int _nextId;
};

