#pragma once

#include "Item.h"

class Key : public Item
{
public:
	Key();
	~Key();
	virtual std::string getType();
};

