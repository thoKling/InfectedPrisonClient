#pragma once

#include <SFML/Graphics.hpp>

class PlayerController;

class PlayersManager
{
public:
	static void destroyChars();

	// Méthode qui permet de créer un nouveau personnage
	static unsigned int createPlayer(const sf::Vector2f& pos);

	// Méthode qui renvoit la liste des personnages
	static std::map<unsigned int, PlayerController*> getPlayers();

	// Procédure qui dessine les personnages
	static void manageDraw(sf::RenderWindow& window);

	// Procédure qui traite les entrées clavier liées aux personnages
	static void handleInputs(const sf::Event& event);

	// Procédure qui met à jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Liste des personnages
	static std::map<unsigned int, PlayerController*> _players;

	// identifiant suivant servant à la création d'un nouveau personnage
	static unsigned int _nextId;
};

