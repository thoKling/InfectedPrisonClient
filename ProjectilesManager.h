#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"

class TileMap;

class ProjectilesManager
{
public:
	static void deleteAllProjectiles();
	// M�thode qui permet de cr�er un nouveau projectile, renvoit son id
	static unsigned int createProjectile(const sf::Vector2f& pos, const sf::Vector2f& mousePosition, const std::string typeWeapon, TileMap* map);

	// Proc�dure qui dessine les projectiles
	static void manageDraw(sf::RenderWindow& window);

	// Proc�dure qui met � jour le comportement des projectiles
	static void update(const sf::Vector2f& mousePos);

private:
	// Liste des projectiles
	static std::map<unsigned int, Projectile*> _projectiles;

	// identifiant suivant servant � la cr�ation d'un nouveau projectile
	static unsigned int _nextId;
};

