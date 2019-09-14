#include "World.h"

#include "ProjectilesManager.h"
#include "ZombiesManager.h"
#include "PlayersManager.h"
#include "PlayerController.h"
#include "Player.h"
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
	_window->setView(_mainView);

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
	PlayersManager::destroyChars();
	ZombiesManager::destroyZombies();
}

World* World::getInstance()
{
	return _instance;
}

void World::init(sf::RenderWindow* window, std::string name)
{
	_instance = new World(window);
	// Création du caractère
	PlayersManager::createClientPlayer(name, sf::Vector2f(836, 810));
	HUD::init(window);

}

void World::loadMap(const sf::Vector2i& position)
{
	_currentRegion = new Region("Chunks/map.txt");
}

void World::loadMapFromServer(std::vector<std::vector<int>>& tiles, const sf::Vector2i& position)
{
	_currentRegion = new Region(tiles);
}

void World::update()
{
	// On recupere la position du joueur, on cast en vector2i car les positions flotantes font des problemes dans les vues
	sf::Vector2i playerPos = sf::Vector2i(PlayersManager::getClientPlayer()->getPosition());

	// On centre les vues sur le joueur
	_mainView.setCenter(sf::Vector2f(playerPos));
	// Mise à jour du comportement des personnages
	PlayersManager::update();

	if (!Utils::debugMode) {
		ZombiesManager::update();
		ProjectilesManager::update();
		_currentRegion->update();
	}

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
	_currentRegion->manageDraw(*_window);
	_window->setView(_mainView);
	PlayersManager::manageDrawCharacters(*_window);
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

	PlayersManager::getClientController().manageDrawInventory(*_window);

	_window->setView(_mainView);
}

void World::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	// Récupération des entrées clavier qui concernent les personnages
	PlayersManager::getClientController().handleInputs(mousePixelPos, mousePos, event);
}

ltbl::LightSystem* World::getLightSys()
{
	return &_ls;
}

bool World::isObstacle(const sf::Vector2i& position)
{
	return _currentRegion->isObstacle(position);
}

DroppedItem* World::getItemInRect(const sf::FloatRect& rect)
{
	return _currentRegion->getDroppedItemInRect(rect);
}

void World::dropItem(Item* item, const sf::Vector2f& position) {
	_currentRegion->dropItem(item, position);
}

void World::deleteItem(Item * item, const sf::Vector2f& pos)
{
	_currentRegion->deleteItem(item, pos);
}

void World::addItem(Item * item, const sf::Vector2f & position)
{
	_currentRegion->addItem(item, position);
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

Region* World::getCurrentRegion() {
	return _currentRegion;
}