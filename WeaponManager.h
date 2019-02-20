#pragma once

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();

	// M�thode qui permet de cr�er une nouvelle arme en fonction de sa fr�quence de tir, de la capacit� de son chargeur et de sa vitesse de rechargement
	unsigned int createWeapon();

private:
	// Liste des armes
	std::map<unsigned int, Weapon*> _weapons;

	// identifiant suivant servant � la cr�ation d'une nouvelle arme
	unsigned int _nextId;
};

