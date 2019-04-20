#include "InventoryView.h"
#include "Inventory.h"
#include "TextureManager.h"
#include "MapUtils.h"

#include <iostream>


InventoryView::InventoryView(Inventory* inventory):
	_inventory(inventory),
	_isDragging(false),
	_blur(sf::Vector2f(WINDOWS_WIDTH, WINDOWS_HEIGHT))
{
	/** Design **/
	
	//On défini le flou
	_blur.setFillColor(sf::Color(0, 0, 0, 160));
	//la texture de l'inventaire
	sf::Texture* textureInventory = TextureManager::loadText("Ressources/PNG/Inventory.png");
	_inventoryShape.setTexture(textureInventory);
	_inventoryShape.setPosition(_baseTop, _baseLeft);

	for (int i = 0; i < WINDOWS_HEIGHT/ TILESIZE; i++) {
		std::vector<Item*> vect(WINDOWS_WIDTH / TILESIZE, nullptr);
		/*for (int j = 0; j < WINDOWS_WIDTH / TILESIZE; j++) {
			vect.push_back(nullptr);
		}*/
		_itemOnScreen.push_back(vect);
	}
	_selectedItem = nullptr;
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

	target.draw(_blur);

	Item* item;
	target.draw(_inventoryShape);
	//Pour chaque case
	//for (int y = 0; y < _baseHeight/ TILESIZE; y++) {
	//	for (int x = 0; x < _baseWidth/ TILESIZE; x++) {
	//		//On dessine la case
	//		cell.setPosition(_baseLeft + x * TILESIZE, _baseTop + y * TILESIZE);
	//		target.draw(cell);
	//		//Si il y a un item on le dessine
	//		item = _itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x];
	//		if (item) {
	//			sf::Sprite sprite = item->getSprite();
	//			const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
	//			sprite.setScale(62.0 / sprite.getTexture()->getSize().x, 62.0 / sprite.getTexture()->getSize().y);
	//			sprite.setPosition(_baseLeft + x * TILESIZE, _baseTop + y * TILESIZE);
	//			target.draw(sprite);
	//			sprite.setScale(initSpriteScale);
	//		}
	//	}
	//}
	
	//affichage de l'objet courrant
	sf::RectangleShape cellCurrentItem(sf::Vector2f(126, 126));
	cellCurrentItem.setFillColor(sf::Color(50, 50, 50));
	cellCurrentItem.setOutlineColor(sf::Color(166, 166, 166));
	cellCurrentItem.setOutlineThickness(1);
	cellCurrentItem.setPosition(_baseLeft - 3* TILESIZE, _baseTop + _baseHeight - 2 * TILESIZE);
	target.draw(cellCurrentItem);
	Item* currentItem = _itemOnScreen[_baseTop/ TILESIZE + _baseHeight/ TILESIZE - 2][_baseLeft / TILESIZE - 3];
	if (currentItem) {
		sf::Sprite sprite = currentItem->getSprite();
		const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
		sprite.setScale(126.0 / sprite.getTexture()->getSize().x, 126.0 / sprite.getTexture()->getSize().y);
		sprite.setPosition(_baseLeft - 3* TILESIZE + 1, _baseTop + _baseHeight - 2 * TILESIZE + 1);
		target.draw(sprite);
		sprite.setScale(initSpriteScale);
	}

	//affichage de l'item selectionné
	if (_selectedItem) {
		sf::Sprite sprite = _selectedItem->getSprite();
		const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
		sprite.setScale(126.0 / sprite.getTexture()->getSize().x, 126.0 / sprite.getTexture()->getSize().y);
		
		sprite.setPosition(_selectedItemLocation.x, _selectedItemLocation.y);
		target.draw(sprite);
		sprite.setScale(initSpriteScale);
	}
		

	target.setView(temp);
}

void InventoryView::update(const sf::Vector2f& mousePos)
{
	std::vector<Item*> emptyVect(WINDOWS_WIDTH / TILESIZE, nullptr);
	_itemOnScreen.clear();
	_itemOnScreen.assign(WINDOWS_HEIGHT / TILESIZE, std::vector<Item*>(WINDOWS_WIDTH / TILESIZE, nullptr));
	
	int addedItem = 0;
	//Mise à jour du tableau _itemOnScreen
	for (auto const& item : _inventory->getItems()) {
		if (item == _inventory->getCurrentItem() && item != _selectedItem) {
			_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 3] = item;
			_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 2] = item;
			_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 1][_baseLeft / TILESIZE - 3] = item;
			_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 1][_baseLeft / TILESIZE - 2] = item;
		}
		else if(item != _selectedItem){
			_itemOnScreen[_baseTop / TILESIZE + floor(addedItem / (_baseHeight / TILESIZE))][_baseLeft / TILESIZE + fmod(addedItem, _baseWidth / TILESIZE)] = item;
			addedItem++;
		}
	}

	//mise à jour de la position du selected item
	if (_selectedItem) {
		_selectedItemLocation = mousePos;
	}
}

void InventoryView::handleInputs(const sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!_isDragging) {
			int x = (int)event.mouseButton.x / TILESIZE;
			int y = (int)event.mouseButton.y / TILESIZE;

			_selectedItem = _itemOnScreen[(int)event.mouseButton.y / TILESIZE][(int)event.mouseButton.x / TILESIZE];
			_isDragging = true;
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (_selectedItem) {
			//drop();
			_selectedItem = nullptr;
		}
		_isDragging = false;
	}
}
