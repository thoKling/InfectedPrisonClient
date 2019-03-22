#pragma once

#include <SFML/Graphics.hpp>

#include "CharactersManager.h"
#include "Region.h"
#include "Utils.h"
#include <unordered_map>

class World
{
///
/// Singleton, il faut l'initialiser pour créer l'instance
///
public:
	static World* getInstance();
	static void init(sf::RenderWindow* window);
private:
	World(sf::RenderWindow* window);
	~World();

	static World* _instance;

public:
	// On charge une nouvelle map
	void loadMap(const std::vector<std::vector<int>>& tiles, const sf::Vector2i& position);

	// Update les différentes entitées en jeux
	void update(sf::Vector2f mousePos);
	void draw();
	void handleInputs(const sf::Event& event);

	// Getters
	ltbl::LightSystem* getLightSys();

	// Utils
	bool isObstacle(const sf::Vector2i& position);
	Item* getNearestItemInRange(const sf::Vector2f& position, unsigned int range);
	void dropItem(Item* item, const sf::Vector2f& position);
private:
	sf::RenderWindow* _window;

	///
	/// Les vues
	///
	sf::View _mainView; // Vue principale centrée sur le personnage 
	sf::View _minimapView; // Vue de la minicarte centrée sur le personnage
	void drawMinimap();

	///
	/// Les éléments du jeu
	///
	Region* _currentRegion;
	std::unordered_map<sf::Vector2i, Region*, vector2i_hash<int>> _regions;

	///
	/// Le système de lumières
	///
	ltbl::LightSystem _ls;
	sf::Sprite _lightSprite;
	sf::RenderStates _lightRenderStates;
	sf::Texture _penumbraTexture;
	sf::Shader _unshadowShader;
	sf::Shader _lightOverShapeShader;
};

