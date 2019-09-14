#include "ViewUtils.h"

void ViewUtils::init(sf::RenderWindow* window)
{
	_tilesize = 64;
	_height = 512;
	_width = 1024;
}

int ViewUtils::getTileSize() {
	return _tilesize;
}

void ViewUtils::setTileSize(int size) {
	_tilesize = size;
}

int ViewUtils::getHeight() {
	return _height;
}

void ViewUtils::setHeight(int height) {
	_height = height;
}

int ViewUtils::getWidth() {
	return _width;
}

void ViewUtils::setWidth(int width) {
	_width = width;
}
