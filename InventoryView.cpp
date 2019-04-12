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

	// base de l'inventaire
	float baseWidth = WINDOWS_WIDTH / 2;
	float baseHeight = WINDOWS_HEIGHT - WINDOWS_HEIGHT / 4;
	float baseTop = WINDOWS_HEIGHT / 8;
	float baseLeft = WINDOWS_WIDTH / 4;

	int itemNumber = 0;
	int indexCurrentItem = -1;
	int nbCurrentItemFound = 0;

	//Pour chaque case
	for (int y = 0; y < baseHeight/64; y++) {
		for (int x = 2; x < baseWidth/64; x++) {
			//On dessine la case
			sf::RectangleShape cell(sf::Vector2f(62, 62));
			cell.setFillColor(sf::Color(50, 50, 50));
			cell.setOutlineColor(sf::Color(166, 166, 166));
			cell.setOutlineThickness(1);
			cell.setPosition(baseLeft + x * 64, baseTop + y * 64);
			target.draw(cell);
			//Si il y a un item on le dessine
			if ((itemNumber + nbCurrentItemFound < _inventory->getItems().size())) {
				Item* item = _inventory->getItems()[itemNumber+nbCurrentItemFound];
				if (item != _inventory->getCurrentItem()) {
					sf::Sprite sprite = item->getSprite();
					const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
					sprite.setScale(62.0 / sprite.getTexture()->getSize().x, 62.0 / sprite.getTexture()->getSize().y);
					sprite.setPosition(baseLeft + (fmod(itemNumber, baseWidth/64)+2) * 64, baseTop + floor(itemNumber / (baseHeight / 64)) * 64);
					target.draw(sprite);
					
					sprite.setScale(initSpriteScale);
					itemNumber++;
				}
				else {
					indexCurrentItem = itemNumber;
					nbCurrentItemFound = 1;
				}
			}
		}
	}
	
	//affichage de l'objet courrant
	sf::RectangleShape cell(sf::Vector2f(126, 126));
	cell.setFillColor(sf::Color(50, 50, 50));
	cell.setOutlineColor(sf::Color(166, 166, 166));
	cell.setOutlineThickness(1);
	cell.setPosition(baseLeft-64, baseTop + baseHeight - 2 * 64);
	target.draw(cell);
	if (indexCurrentItem != -1) {
		Item* currentItem = _inventory->getItems()[indexCurrentItem];
		sf::Sprite sprite = currentItem->getSprite();
		const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
		sprite.setScale(126.0 / sprite.getTexture()->getSize().x, 126.0 / sprite.getTexture()->getSize().y);
		sprite.setPosition(baseLeft -64 +1, baseTop + baseHeight - 2 * 64 +1 );
		target.draw(sprite);
		sprite.setScale(initSpriteScale);
	}
	

	target.setView(temp);
}

void InventoryView::handleInputs(const sf::Event& event)
{
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (rect.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			dragging = true;
			mouseRectOffset.x = event.mouseButton.x - rect.getGlobalBounds().left - rect.getOrigin().x;
			mouseRectOffset.y = event.mouseButton.y - rect.getGlobalBounds().top - rect.getOrigin().y;
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseClicked = false;
		dragging = false;
	}*/
}
