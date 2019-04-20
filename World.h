#pragma once

#include <SFML/Graphics.hpp>

#include "Region.h"
#include "Utils.h"
#include "PlayerController.h"

class World
{
///
/// Singleton, il faut l'initialiser pour cr�er l'instance
///
public:
	static World* getInstance();
	static void init(sf::RenderWindow* window, std::string name);
private:
	World(sf::RenderWindow* window);
	~World();

	static World* _instance;

public:
	// On charge une nouvelle map
	void loadMap(const sf::Vector2i& position);

	// Update les diff�rentes entit�es en jeux
	void update();
	void draw();
	void handleInputs(const sf::Vector2f& mousePos, const sf::Event& event);

	// Getters
	ltbl::LightSystem* getLightSys();

	// Utils
	bool isObstacle(const sf::Vector2i& position);
	Item* getItemInRect(const sf::FloatRect& rect);
	void dropItem(Item* item, const sf::Vector2f& position);

	std::vector<std::vector<int>> getTiles();

	void gameOver();
	bool getGameOver();

private:
	bool _gameOver = false;

	sf::RenderWindow* _window;

	///
	/// Les vues
	///
	sf::View _mainView; // Vue principale centr�e sur le personnage 

	///
	/// Les �l�ments du jeu
	///
	Region* _currentRegion;
	//std::unordered_map<sf::Vector2i, Region*, vector2i_hash<int>> _regions;

	///
	/// Le syst�me de lumi�res
	///
	ltbl::LightSystem _ls;
	sf::Sprite _lightSprite;
	sf::RenderStates _lightRenderStates;
	sf::Texture _penumbraTexture;
	sf::Shader _unshadowShader;
	sf::Shader _lightOverShapeShader;
};

