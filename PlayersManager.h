#pragma once

#include <SFML/Graphics.hpp>

class PlayerController;
class Player;

class PlayersManager
{
public:
	static void destroyChars();

	// Méthode qui créer le personnage du client
	static void createClientPlayer(std::string name, const sf::Vector2f& pos);

	// Méthode qui permet de créer un nouveau personnage
	static void createPlayer(std::string name, const sf::Vector2f& pos);

	// Méthode qui renvoit la liste des personnages
	static std::map<std::string, Player*> getPlayers();

	static Player* getPlayer(std::string name);

	static Player* getClientPlayer();

	static PlayerController& getClientController();

	// Procédure qui dessine les personnages
	static void manageDrawCharacters(sf::RenderWindow& window);

	// Procédure qui met à jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Controleur du client 
	static PlayerController _clientPlayerController;

	// Player du client 
	static Player* _clientPlayer;

	// Liste des personnages
	static std::map<std::string, Player*> _playersConnected;
};

