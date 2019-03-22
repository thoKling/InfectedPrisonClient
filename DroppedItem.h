#pragma once

#include "DrawableEntity.h"

class Item;

class DroppedItem : public DrawableEntity
{
public:
	DroppedItem(Item* item);
	~DroppedItem();
	Item* getItem();

private:
	Item* _instance;
};

