#include "Item.h"



void Item::SetStatus(const char * _name, ItemType _type, int _atk, int _def)
{
	Name = new char[strlen(_name) + 1];
	strcpy(Name, _name);
	type = _type;
	PlusAtk = _atk;
	PlusDef = _def;
}

void Item::Init()
{
	Ploc = &loc;
}

Item::Item()
{
}


Item::~Item()
{
	if (Name != NULL) {
		delete[] Name;
		Name = NULL;
	}
}
