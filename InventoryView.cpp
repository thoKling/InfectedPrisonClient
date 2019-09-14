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
	//sf::Texture* textureInventory = TextureManager::loadText("Ressources/PNG/Inventory.png");
	//_inventoryShape.setTexture(textureInventory);
	//_inventoryShape.setPosition(_baseTop, _baseLeft);

	for (int i = 0; i < WINDOWS_HEIGHT/ TILESIZE; i++) {
		std::vector<Item*> vect(WINDOWS_WIDTH / TILESIZE, nullptr);
		_itemOnScreen.push_back(vect);
	}
	_selectedItem = nullptr;
}

InventoryView::~InventoryView()
{
	delete _inventory;
	delete _selectedItem;
	for (auto it = _droppedItems.begin(); it != _droppedItems.end(); ++it) {
		delete *it;
	}
}

void InventoryView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// On récupère d'abord la taille de la fenetre
	/*int windowWidth = target.getSize().x;
	int windowHeight = target.getSize().y;*/


	//On remet la vue actuelle après l'affichage de l'inventaire
	/*sf::View tempView = target.getView();
	target.setView(target.getDefaultView());*/

	target.draw(_blur);

	Item* item;
	sf::RectangleShape cell(sf::Vector2f(TILESIZE, TILESIZE));
	cell.setFillColor(sf::Color(50, 50, 50));
	cell.setOutlineColor(sf::Color(166, 166, 166));
	cell.setOutlineThickness(1);
	//Pour chaque case
	for (int y = 0; y < _baseHeight / TILESIZE; y++) {
		for (int x = 0; x < _baseWidth / TILESIZE; x++) {
			//On dessine la case
			cell.setPosition(_baseLeft + x * TILESIZE, _baseTop + y * TILESIZE);
			target.draw(cell);
			//Si il y a un item qui n'est pas l'item en main ou séléctioné, on le dessine
			item = _itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x];
			if (item && item != _inventory->getCurrentItem() && item != _selectedItem) {
				sf::Sprite sprite = item->getSprite();
				sprite.setScale(TILESIZE / (float)sprite.getTexture()->getSize().x, TILESIZE / (float)sprite.getTexture()->getSize().y);
				sprite.setPosition(_baseLeft + x * TILESIZE, _baseTop + y * TILESIZE);
				target.draw(sprite);
			}
		}
	}

	//affichage de l'objet courrant
	sf::RectangleShape cellCurrentItem(sf::Vector2f(2 * TILESIZE, 2 * TILESIZE));
	cellCurrentItem.setFillColor(sf::Color(50, 50, 50));
	cellCurrentItem.setOutlineColor(sf::Color(166, 166, 166));
	cellCurrentItem.setOutlineThickness(1);
	cellCurrentItem.setPosition(_baseLeft - 3 * TILESIZE, _baseTop + _baseHeight - 2 * TILESIZE);
	target.draw(cellCurrentItem);
	Item* currentItem = _itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 3];
	if (currentItem && currentItem != _selectedItem) {
		sf::Sprite sprite = currentItem->getSprite();
		const sf::Vector2f initSpriteScale(sprite.getScale().x, sprite.getScale().y);
		sprite.setScale((2.0 * TILESIZE) / sprite.getTexture()->getSize().x, (2.0 * TILESIZE) / sprite.getTexture()->getSize().y);
		sprite.setPosition(_baseLeft - 3 * TILESIZE + 1, _baseTop + _baseHeight - 2 * TILESIZE + 1);
		target.draw(sprite);
		sprite.setScale(initSpriteScale);
	}

	//affichage de l'item selectionné
	if (_selectedItem) {

		sf::Sprite sprite = _selectedItem->getSprite();
		sprite.setScale((1.5 * TILESIZE) / sprite.getTexture()->getSize().x, (1.5 * TILESIZE) / sprite.getTexture()->getSize().y);
		
		sprite.setPosition(_selectedItemLocation.x - (sprite.getGlobalBounds().width/2) , 
			_selectedItemLocation.y - (sprite.getGlobalBounds().height/2));


		target.draw(sprite);
	}
	//target.setView(tempView);
}

void InventoryView::update()
{
	Item* item = _itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 3];
	Item* currentItem = _inventory->getCurrentItem();
	if (item != currentItem) {
		_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 3] = currentItem;
		_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 2][_baseLeft / TILESIZE - 2] = currentItem;
		_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 1][_baseLeft / TILESIZE - 3] = currentItem;
		_itemOnScreen[_baseTop / TILESIZE + _baseHeight / TILESIZE - 1][_baseLeft / TILESIZE - 2] = currentItem;
	}
}

void InventoryView::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!_isDragging) {
			float tempX = mousePixelPos.x / (float) TILESIZE;
			float tempY = mousePixelPos.y / (float) TILESIZE;
			int x = static_cast<int>(tempX);
			int y = static_cast<int>(tempY);

			if (!(x < 0 || y < 0 || x >= WINDOWS_WIDTH / TILESIZE || y >= WINDOWS_HEIGHT / TILESIZE )) {
				
				_selectedItem = _itemOnScreen[y][x];
				_isDragging = true;
			}
		}
		else {
			_selectedItemLocation.x =mousePixelPos.x;
			_selectedItemLocation.y = mousePixelPos.y;
		}
		
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (_selectedItem) {
			drop();
			_selectedItem = nullptr;
		}
		_isDragging = false;
	}
}

void InventoryView::addItem(Item* newItem) {
	Item* currentItem = _inventory->getCurrentItem();
	// On l'ajoute dans les cases seulement si ce n'est pas l'item courant
	if (newItem != currentItem) {
		for (int y = 0; y < _baseHeight / TILESIZE; y++) {
			for (int x = 0; x < _baseWidth / TILESIZE; x++) {
				Item* item = _itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x];
				// S'il n'y a pas d'item a cet emplacement
				if (!item) {
					_itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x] = newItem;
					return;
				}
			}
		}
	}
}

void InventoryView::removeItem(Item* deletedItem) {
	for (auto it = _itemOnScreen.begin(); it != _itemOnScreen.end(); ++it) {
		//vector::erase will move object order
		//it->erase(std::remove(it->begin(), it->end(), deletedItem), it->end());

		auto itemIt = std::find(it->begin(), it->end(), deletedItem);
		if (itemIt != it->end()) {
			delete *itemIt;
			*itemIt = nullptr;
		}
	}
}

void InventoryView::drop() {
	float itemPosX = _selectedItemLocation.x;
	float itemPosY = _selectedItemLocation.y;

	//On test si l'endroit de drop est une case de l'inventaire ou la main
	if ((!((itemPosX < _baseLeft || itemPosY < _baseTop || itemPosX >= _baseLeft + _baseWidth || itemPosY >= _baseTop + _baseHeight))) //inventaire
		|| (((itemPosY > _baseTop + _baseHeight - 2*TILESIZE) && (itemPosY < _baseTop + _baseHeight )) //main
		&& ((itemPosX > _baseLeft - 3*TILESIZE) || (itemPosX < _baseLeft - TILESIZE)))) {
		float tempX = itemPosX / static_cast<float>(TILESIZE);
		float tempY = itemPosY / static_cast<float>(TILESIZE);
		int x = static_cast<int>(tempX);
		int y = static_cast<int>(tempY);
		Item* item = _itemOnScreen[y][x];
		// Si il n'y a pas d'item à l'endroit de drop
		if (!item) {
			moveItem(item, x, y);
		}
	}
	else if (!(itemPosX < 0 || itemPosX > WINDOWS_WIDTH || itemPosY < 0 || itemPosY > WINDOWS_HEIGHT) ) {
		_droppedItems.push_back(_selectedItem);
		//removing selecting item
		removeSelectedItemFromHand();
		removeSelectedItemFromInventory(_inventory->getCurrentItem());
	}
}

void InventoryView::moveItem(Item* item, int x, int  y) {
	
	Item* prevItem = _inventory->getCurrentItem();

	removeSelectedItemFromHand();

	// Si l'item est placé dans la main
	if (((y == (_baseTop + _baseHeight) / TILESIZE - 2) || y == (_baseTop + _baseHeight) / TILESIZE - 1)
		&& ((x == _baseLeft / TILESIZE - 3) || (x == _baseLeft / TILESIZE - 2))) {
		if (_selectedItem->getItemType() == ItemType::Gun) {
			_inventory->setCurrentItem(_selectedItem);
			removeSelectedItemFromInventory(prevItem);
		}
		else
			return;
	}
	else {
		removeSelectedItemFromInventory(prevItem);
		_itemOnScreen[y][x] = _selectedItem;
	}
}

std::vector<Item*> InventoryView::getDroppedItems() {
	return _droppedItems;
}

void InventoryView::deleteDroppedItems() {
	_droppedItems.clear();
}

void InventoryView::removeSelectedItemFromHand() {
	// Si l'item selectionné était en main
	if (_selectedItem == _inventory->getCurrentItem()) {
		_inventory->setCurrentItem(nullptr);
	}
}

void InventoryView::removeSelectedItemFromInventory(Item* itemInHand) {
	// Si c'était pas en main
	if (_selectedItem != itemInHand) {
		for (int y = 0; y < _baseHeight / TILESIZE; y++) {
			for (int x = 0; x < _baseWidth / TILESIZE; x++) {
				Item* item = _itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x];
				// S'il n'y a pas d'item a cet emplacement
				if (item == _selectedItem) {
					_itemOnScreen[_baseTop / TILESIZE + y][_baseLeft / TILESIZE + x] = nullptr;
				}
			}
		}
	}
}