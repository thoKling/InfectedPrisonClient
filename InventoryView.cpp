#include "InventoryView.h"
#include "Inventory.h"
#include "TextureManager.h"

#include <iostream>


InventoryView::InventoryView(Inventory* inventory):
	_inventory(inventory)
{
	for (int i = 0; i < WINDOWS_HEIGHT/ 64; i++) {
		std::vector<Item*> vect(WINDOWS_WIDTH / 64, nullptr);
		/*for (int j = 0; j < WINDOWS_WIDTH / 64; j++) {
			vect.push_back(nullptr);
		}*/
		_itemOnScreen.push_back(vect);
	}
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

	//Pour chaque case
	for (int y = 0; y < _baseHeight/64; y++) {
		for (int x = 0; x < _baseWidth/64; x++) {
			//On dessine la case
			sf::RectangleShape cell(sf::Vector2f(62, 62));
			cell.setFillColor(sf::Color(50, 50, 50));
			cell.setOutlineColor(sf::Color(166, 166, 166));
			cell.setOutlineThickness(1);
			cell.setPosition(_baseLeft + x * 64, _baseTop + y * 64);
			target.draw(cell);
			//Si il y a un item on le dessine
			Item* item = _itemOnScreen[_baseTop / 64 + y][_baseLeft / 64 + x];
			if (item) {
				sf::Sprite sprite = item->getSprite();
				const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
				sprite.setScale(62.0 / sprite.getTexture()->getSize().x, 62.0 / sprite.getTexture()->getSize().y);
				sprite.setPosition(_baseLeft + x * 64, _baseTop + y * 64);
				target.draw(sprite);
				sprite.setScale(initSpriteScale);
			}
		}
	}
	
	//affichage de l'objet courrant
	sf::RectangleShape cell(sf::Vector2f(126, 126));
	cell.setFillColor(sf::Color(50, 50, 50));
	cell.setOutlineColor(sf::Color(166, 166, 166));
	cell.setOutlineThickness(1);
	cell.setPosition(_baseLeft - 3*64, _baseTop + _baseHeight - 2 * 64);
	target.draw(cell);
	Item* currentItem = _itemOnScreen[_baseLeft/64 - 3][_baseTop/64 + _baseHeight/64 - 2];
	if (currentItem) {
		sf::Sprite sprite = currentItem->getSprite();
		const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
		sprite.setScale(126.0 / sprite.getTexture()->getSize().x, 126.0 / sprite.getTexture()->getSize().y);
		sprite.setPosition(_baseLeft - 3*64 + 1, _baseTop + _baseHeight - 2 * 64 + 1);
		target.draw(sprite);
		sprite.setScale(initSpriteScale);
	}

	

	target.setView(temp);
}

void InventoryView::update()
{
	std::vector<Item*> emptyVect(WINDOWS_WIDTH / 64, nullptr);
	_itemOnScreen.clear();
	_itemOnScreen.assign(WINDOWS_HEIGHT / 64, std::vector<Item*>(WINDOWS_WIDTH / 64, nullptr));
	
	int addedItem = 0;
	//Mise à jour du tableau _itemOnScreen
	for (auto const& item : _inventory->getItems()) {
		if (item != _inventory->getCurrentItem()) {
			_itemOnScreen[_baseTop / 64 + floor(addedItem / (_baseHeight / 64))][_baseLeft / 64 + fmod(addedItem, _baseWidth / 64)] = item;
			addedItem++;
		}
		else
			_itemOnScreen[_baseLeft / 64 - 3][_baseTop / 64 + _baseHeight / 64 - 2] = item;
	}
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
