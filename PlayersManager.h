#pragma once

#include <SFML/Graphics.hpp>

class PlayerController;

class PlayersManager
{
public:
	static void destroyChars();

	// M�thode qui permet de cr�er un nouveau personnage
	static unsigned int createPlayer(const sf::Vector2f& pos);

	// M�thode qui renvoit la liste des personnages
	static std::map<unsigned int, PlayerController*> getPlayers();

	// Proc�dure qui dessine les personnages
	static void manageDraw(sf::RenderWindow& window);

	// Proc�dure qui traite les entr�es clavier li�es aux personnages
	static void handleInputs(const sf::Event& event);

	// Proc�dure qui met � jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Liste des personnages
	static std::map<unsigned int, PlayerController*> _players;

	// identifiant suivant servant � la cr�ation d'un nouveau personnage
	static unsigned int _nextId;
};

