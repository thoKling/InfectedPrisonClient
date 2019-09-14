#pragma once

#include <SFML/Graphics.hpp>

class ViewUtils
{
public:

	static void init(sf::RenderWindow* window);
	static int getTileSize();
	static void setTileSize(int size);
	static int getHeight();
	static void setHeight(int height);
	static int getWidth();
	static void setWidth(int width);

private:
	static int _tilesize;
	static int _height;
	static int _width;
	sf::RenderWindow* _window;
};

