#include "Key.h"

#include "TextureManager.h"

Key::Key()
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/theKey.png"));
}


Key::~Key()
{
}

std::string Key::getType()
{
	return "Key";
}
