#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class TextureManager
{
public:
	// Charge une texture, la stocke puis la renvoit. Si la texture a d�j� �t� charg�e, la renvoit.
	static sf::Texture& loadText(std::string path);
private:
	static std::map<std::string, sf::Texture*> _textMap;
};

