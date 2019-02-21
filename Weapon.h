#pragma once

#include <SFML/Graphics.hpp>
#include "ProjectilesManager.h"
#include "AudioManager.h"

class Character;

class Weapon
{
private:
	int _ammo;
	bool _isReloading;
	// l'arme est elle en capacité de tirer
	bool _isFireable;
	// nombre de tick depuis la dernière update du rechargement( 1tick = 0.06s), nous servant à ne pas actualiser trop souvent
	int _tickSinceReloadingUpdate;
	// nombre de tick depuis la dernière update du tir( 1tick = 0.06s), nous servant à ne pas actualiser trop souvent
	int _tickSinceFiringUpdate;
	// nombre de balles dans un chargeur
	const int _capacity;
	// nombre de secondes pour recharger
	const float _reloadSpeed;
	// nombre de balles par secondes
	const float _fireRate;

	// type de l'arme
	std::string _type;

public:
	Weapon();
	~Weapon();

	void fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager, const sf::Vector2f& firingPosition);
	void reload();
	void update();
};

