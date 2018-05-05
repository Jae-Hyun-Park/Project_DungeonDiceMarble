#include "Tile.h"


void Tile::init(SDLGameObject * obj)
{
	tile = obj->GetComponent<Texture>();
	tile->gameObject = obj;
	monster = NULL;
	item = NULL;
}

Tile::Tile()
{
}


Tile::~Tile()
{
	
}
