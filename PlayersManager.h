#pragma once

#include <SFML/Graphics.hpp>

class PlayerController;
class Player;

class PlayersManager
{
public:
	static void destroyChars();

	// M�thode qui cr�er le personnage du client
	static void createClientPlayer(std::string name, const sf::Vector2f& pos);

	// M�thode qui permet de cr�er un nouveau personnage
	static void createPlayer(std::string name, const sf::Vector2f& pos);

	// M�thode qui renvoit la liste des personnages
	static std::map<std::string, Player*> getPlayers();

	static Player* getPlayer(std::string name);

	static Player* getClientPlayer();

	static PlayerController& getClientController();

	// Proc�dure qui dessine les personnages
	static void manageDrawCharacters(sf::RenderWindow& window);

	// Proc�dure qui met � jour le comportement des personnages
	static void update(const sf::Vector2f& mousePos);

private:
	// Controleur du client 
	static PlayerController _clientPlayerController;

	// Player du client 
	static Player* _clientPlayer;

	// Liste des personnages
	static std::map<std::string, Player*> _playersConnected;
};

