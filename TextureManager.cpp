#include "TextureManager.h"
#include "Utils.h"

#include <iostream>

std::map<std::string, sf::Texture*> TextureManager::_textMap;

sf::Texture* TextureManager::loadText(const std::string& path)
{
	// On recupere juste le nom de la texture
	std::vector<std::string> splited = Utils::split(path, "/");
	std::string textName = splited[splited.size()-1];

	// On vérifie qu'on ne l'a pas déjà chargée
	if (_textMap.find(textName) != _textMap.end()) {
		//std::cout << "Déjà chargée" << std::endl;
		return _textMap[textName];
	}

	std::cout << "Chargement nouvelle texture " << textName << std::endl;

	// On charge la texture
	sf::Texture* temp = new sf::Texture();
	temp->setSmooth(true);
	if (!temp->loadFromFile(path))
		throw std::string("Impossible de charger la texture " + textName);
	
	// On la stock
	_textMap[textName] = temp;

	// On la renvoit
	return _textMap[textName];
}
