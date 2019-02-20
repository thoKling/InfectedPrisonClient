#pragma once

#include <SFML/Graphics.hpp>
#include "ProjectilesManager.h"
#include "AudioManager.h"

class Weapon
{
private:
	int _ammo;
	bool isReloading;
	std::string _type;
	const int _capacity;
	const int _reloadSpeed;
	const int _fireRate;

public:
	Weapon();
	~Weapon();

	void fire(const sf::Vector2f& mousePos, ProjectilesManager& projectilesManager, AudioManager& audioManager, const sf::Vector2f& firingPosition);
	void reload();
};

