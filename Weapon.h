#pragma once

#include <SFML/Graphics.hpp>

#include "Item.h"

class Weapon : public Item
{
private:
	int _ammo;
	// est en train de recharger
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

	virtual void use(Character* charac);
	virtual bool isReloading();
	virtual void reload();
	virtual void update();
	virtual unsigned int getAmmo();
	virtual std::string getWeaponType();
};

