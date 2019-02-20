#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"

class TileMap;

class CharactersManager
{
public:
	CharactersManager(TileMap* map);
	~CharactersManager();

	// Méthode qui permet de créer un nouveau personnage
	unsigned int createCharacter(const sf::Vector2f& pos);

	// Méthode qui renvoit la liste des personnages
	std::map<unsigned int, Character*> getCharacters();

	// Procédure qui dessine les personnages
	void manageDraw(sf::RenderWindow& window);

	// Procédure qui récupère et traite les entrées clavier liées aux personnages
	void handleInputs(const sf::Event& event);

	// Procédure qui met à jour le comportement des personnages
	void update(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager);

private:
	// Liste des personnages
	std::map<unsigned int, Character*> _characters;

	TileMap* _map;

	// identifiant suivant servant à la création d'un nouveau personnage
	unsigned int _nextId;
};

