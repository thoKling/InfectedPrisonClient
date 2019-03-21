#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"

class CharactersManager
{
public:
	static void destroyChars();

	// M�thode qui permet de cr�er un nouveau personnage
	static unsigned int createCharacter(const sf::Vector2f& pos);

	// M�thode qui renvoit la liste des personnages
	static std::map<unsigned int, Character*> getCharacters();

	// Proc�dure qui dessine les personnages
	static void manageDraw(sf::RenderWindow& window);

	// Proc�dure qui traite les entr�es clavier li�es aux personnages
	static void handleInputs(const sf::Event& event);

	// Proc�dure qui met � jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Liste des personnages
	static std::map<unsigned int, Character*> _characters;

	// identifiant suivant servant � la cr�ation d'un nouveau personnage
	static unsigned int _nextId;
};

