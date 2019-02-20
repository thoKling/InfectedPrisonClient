#include "WeaponManager.h"



WeaponManager::WeaponManager()
{
	_nextId = 0;
}

WeaponManager::~WeaponManager()
{
	for (std::map<unsigned int, Weapon*>::iterator it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		delete it->second;
	}
}

// M�thode qui permet de cr�er une nouvelle arme en fonction de sa fr�quence de tir, de la capacit� de son chargeur et de sa vitesse de rechargement
unsigned int WeaponManager::createWeapon() {
	_weapons[_nextId] = new Weapon();
	_nextId++;
	return _nextId - 1;
}
