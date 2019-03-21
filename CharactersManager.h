#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"

class CharactersManager
{
public:
	static void destroyChars();

	// Méthode qui permet de créer un nouveau personnage
	static unsigned int createCharacter(const sf::Vector2f& pos);

	// Méthode qui renvoit la liste des personnages
	static std::map<unsigned int, Character*> getCharacters();

	// Procédure qui dessine les personnages
	static void manageDraw(sf::RenderWindow& window);

	// Procédure qui traite les entrées clavier liées aux personnages
	static void handleInputs(const sf::Event& event);

	// Procédure qui met à jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Liste des personnages
	static std::map<unsigned int, Character*> _characters;

	// identifiant suivant servant à la création d'un nouveau personnage
	static unsigned int _nextId;
};

