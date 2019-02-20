#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ProjectilesManager
{
public:
	ProjectilesManager();
	~ProjectilesManager();

	// M�thode qui permet de cr�er un nouveau projectile
	unsigned int createProjectile(const sf::Vector2f& pos, const sf::Vector2f& mousePosition);

	// Proc�dure qui dessine les projectiles
	void manageDraw(sf::RenderWindow& window);


	// Proc�dure qui met � jour le comportement des projectiles
	void update(const sf::Vector2f& mousePos);

private:
	// Liste des projectiles
	std::map<unsigned int, Projectile*> _projectiles;

	// identifiant suivant servant � la cr�ation d'un nouveau projectile
	unsigned int _nextId;
};

