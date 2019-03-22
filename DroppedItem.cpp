#include "DroppedItem.h"
#include "Item.h"

DroppedItem::DroppedItem(Item* item)
{
	_instance = item;
	_sprite = item->getSprite();
}


DroppedItem::~DroppedItem()
{
}

Item * DroppedItem::getItem()
{
	return _instance;
}
