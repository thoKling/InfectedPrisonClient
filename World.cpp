#include "World.h"

#include "ProjectilesManager.h"
#include "ZombiesManager.h"
#include "AudioManager.h"
#include "Utils.h"
#include "HUD.h"

World* World::_instance = nullptr;

World::World(sf::RenderWindow* window) :
	_window(window)
{
	// on créé les vues
	_mainView = window->getDefaultView();
	_mainView.zoom(1.5f);
	//_window->setView(_mainView);
	_minimapView = _mainView;
	_minimapView.zoom(1.5);
	// Dans un coin en haut à droite
	_minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

	// Système de lumières
	_penumbraTexture.loadFromFile("LTBL2/resources/penumbraTexture.png");
	_penumbraTexture.setSmooth(true);
	_unshadowShader.loadFromFile("LTBL2/resources/unshadowShader.vert", "LTBL2/resources/unshadowShader.frag");
	_lightOverShapeShader.loadFromFile("LTBL2/resources/lightOverShapeShader.vert", "LTBL2/resources/lightOverShapeShader.frag");
	_ls.create(sf::FloatRect(-1000.0f, -1000.0f, 1000.0f, 1000.0f), window->getSize(), _penumbraTexture, _unshadowShader, _lightOverShapeShader);
	_lightRenderStates.blendMode = sf::BlendMultiply;
	_lightSprite.setTexture(_ls.getLightingTexture());
}

World::~World()
{
	ProjectilesManager::deleteAllProjectiles();
	CharactersManager::destroyChars();
	ZombiesManager::destroyZombies();
}

World* World::getInstance()
{
	return _instance;
}

void World::init(sf::RenderWindow* window)
{
	_instance = new World(window);
	// Création du caractère
	CharactersManager::createCharacter(sf::Vector2f(128, 200));
	HUD::init(window);
}

void World::loadMap(const std::vector<std::vector<int>>& tiles, const sf::Vector2i& position)
{
	// Si on a pas déjà chargé cette région
	//if (_regions.find(position) != _regions.end())
		//_regions[sf::Vector2i(position)] = new Region(_ls, tiles);
	_currentRegion = new Region(tiles);
	// Création d'un zombie
	ZombiesManager::createZombie(sf::Vector2f(800, 500));
}

void World::update(sf::Vector2f mousePos)
{
	// Mise à jour du comportement des personnages
	CharactersManager::update(mousePos);
	if (!Utils::debugMode) {
		ZombiesManager::update();
		ProjectilesManager::update();
		_currentRegion->update();
	}

	// On recupere la position du joueur, on cast en vector2i car les positions flotantes font des problemes dans les vues
	sf::Vector2i playerPos = sf::Vector2i(CharactersManager::getCharacters()[0]->getPosition());

	// On centre les vues sur le joueur
	_mainView.setCenter(CharactersManager::getCharacters()[0]->getPosition());//sf::Vector2f(playerPos));
	_minimapView.setCenter(sf::Vector2f(playerPos));

	//si la fenetre n'a pas le focus on eteint la musique
	if (_window->hasFocus() && !AudioManager::isMainThemePlayed()) {
		AudioManager::playMainTheme();
	}
	else if (!_window->hasFocus() && AudioManager::isMainThemePlayed()) {
		AudioManager::stopMainTheme();
	}
}

void World::draw()
{
	// On fait les différents dessins en commencant par la map
	_window->setView(_mainView);
	_currentRegion->manageDraw(*_window);
	CharactersManager::manageDraw(*_window);
	ZombiesManager::manageDraw(*_window);
	ProjectilesManager::manageDraw(*_window);

	// On ne dessine pas les ombres si on est en mode debug
	if (!Utils::debugMode) {
		_window->setView(_window->getDefaultView());
		_window->draw(_lightSprite, _lightRenderStates);	// les ombres
		_window->setView(_mainView);
		_ls.render(_mainView, _unshadowShader, _lightOverShapeShader); // les lumières
	}

	_window->setView(_window->getDefaultView());
	HUD::manageDraw(_window);
	_window->setView(_mainView);
}

void World::handleInputs(const sf::Event& event)
{
	// Récupération des entrées clavier qui concernent les personnages
	CharactersManager::handleInputs(event);
}

ltbl::LightSystem* World::getLightSys()
{
	return &_ls;
}

bool World::isObstacle(const sf::Vector2i& position)
{
	return _currentRegion->isObstacle(position);
}

Item * World::getItemInRect(const sf::FloatRect& rect)
{
	return _currentRegion->getItemInRect(rect);
}

void World::dropItem(Item* item, const sf::Vector2f& position) {
	_currentRegion->dropItem(item, position);
}

std::vector<std::vector<int>> World::getTiles()
{
	return _currentRegion->getTiles();
}

void World::gameOver()
{
	_gameOver = true;
}

bool World::getGameOver()
{
	return _gameOver;
}

void World::drawMinimap()
{
	// On dessine la miniMap
	_window->setView(_minimapView);

	// On fait les différents dessins en commencant par la map
	_currentRegion->manageDraw(*_window);
	CharactersManager::manageDraw(*_window);

	//_window->draw(_lightSprite, _lightRenderStates);	// les ombres
	_ls.render(_minimapView, _unshadowShader, _lightOverShapeShader); // les lumières


	// On remet la vue principale
	_window->setView(_mainView);
}
