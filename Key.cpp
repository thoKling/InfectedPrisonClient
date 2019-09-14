#include "Key.h"

#include "TextureManager.h"

Key::Key()
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/theKey.png"));
}


Key::~Key()
{
}

ItemType Key::getType()
{
	return ItemType::Key;
}
