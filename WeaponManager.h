#pragma once

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();

	// Méthode qui permet de créer une nouvelle arme en fonction de sa fréquence de tir, de la capacité de son chargeur et de sa vitesse de rechargement
	unsigned int createWeapon();

private:
	// Liste des armes
	std::map<unsigned int, Weapon*> _weapons;

	// identifiant suivant servant à la création d'une nouvelle arme
	unsigned int _nextId;
};

