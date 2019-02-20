#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ProjectilesManager
{
public:
	ProjectilesManager();
	~ProjectilesManager();

	// Méthode qui permet de créer un nouveau projectile
	unsigned int createProjectile(const sf::Vector2f& pos, const sf::Vector2f& mousePosition);

	// Procédure qui dessine les projectiles
	void manageDraw(sf::RenderWindow& window);


	// Procédure qui met à jour le comportement des projectiles
	void update(const sf::Vector2f& mousePos);

private:
	// Liste des projectiles
	std::map<unsigned int, Projectile*> _projectiles;

	// identifiant suivant servant à la création d'un nouveau projectile
	unsigned int _nextId;
};

