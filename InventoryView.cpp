#include "InventoryView.h"
#include "Inventory.h"
#include "Utils.h"
#include "TextureManager.h"

#include <iostream>


InventoryView::InventoryView(Inventory* inventory):
	_inventory(inventory)
{
}

InventoryView::~InventoryView()
{
	delete _inventory;
}

void InventoryView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//On remet la vue actuelle après l'affichage de l'inventaire
	sf::View temp = target.getView();
	target.setView(target.getDefaultView());

	// Fond flou
	sf::RectangleShape blur(sf::Vector2f(WINDOWS_WIDTH, WINDOWS_HEIGHT));
	blur.setFillColor(sf::Color(0, 0, 0, 160));
	target.draw(blur);

	// Fond de l'inventaire
	float baseWidth = WINDOWS_WIDTH / 2;
	float baseHeight = WINDOWS_HEIGHT - WINDOWS_HEIGHT / 4;
	float baseTop = WINDOWS_HEIGHT / 8;
	float baseLeft = WINDOWS_WIDTH / 4;
	sf::RectangleShape base(sf::Vector2f(baseWidth, baseHeight));
	base.setFillColor(sf::Color(50, 50, 50));
	base.setOutlineColor(sf::Color(166, 166, 166));
	base.setOutlineThickness(1);
	base.setPosition(baseLeft, baseTop);
	target.draw(base);

	int nbCurrentItemFound = 0;

	//Pour chaque case
	for (int y = 0; y < baseHeight/64; y++) {
		for (int x = 0; x < baseWidth/64; x++) {
			//On dessine la case
			sf::RectangleShape cell(sf::Vector2f(62, 62));
			cell.setFillColor(sf::Color(50, 50, 50));
			cell.setOutlineColor(sf::Color(166, 166, 166));
			cell.setOutlineThickness(1);
			cell.setPosition(baseLeft + x * 64, baseTop + y * 64);
			target.draw(cell);
			//Si il y a un item on le dessine
			if (((baseWidth / 64)*y) + x + nbCurrentItemFound < _inventory->getItems().size()) {
				Item* item = _inventory->getItems()[((baseWidth / 64)*y) + x + nbCurrentItemFound];
				if (nbCurrentItemFound == 0 && item == _inventory->getCurrentItem()) {
					nbCurrentItemFound = 1;
					item = _inventory->getItems()[((baseWidth / 64)*y) + x + nbCurrentItemFound];
				}
				if (item != nullptr) {
					sf::Sprite sprite = item->getSprite();
					const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
					sprite.setScale(62.0 / sprite.getTexture()->getSize().x, 62.0 / sprite.getTexture()->getSize().y);
					sprite.setPosition(baseLeft + x * 64, baseTop + y * 64);
					target.draw(sprite);
					sprite.setScale(initSpriteScale);
				}
			}
		}
	}
	//affichage de l'objet courrant


	target.setView(temp);
}
