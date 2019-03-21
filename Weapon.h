#pragma once

#include <SFML/Graphics.hpp>

class Weapon
{
private:
	int _ammo;
	// est en train de recharger
	bool _isReloading;
	// l'arme est elle en capacit� de tirer
	bool _isFireable;
	// nombre de tick depuis la derni�re update du rechargement( 1tick = 0.06s), nous servant � ne pas actualiser trop souvent
	int _tickSinceReloadingUpdate;
	// nombre de tick depuis la derni�re update du tir( 1tick = 0.06s), nous servant � ne pas actualiser trop souvent
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

	void fire(const sf::Vector2f& mousePos, const sf::Vector2f& firingPosition);
	bool needToReload();
	bool isReloading();
	void reload();
	void update();
	std::string getType();
};

