#include "TileMap.h"



TileMap::TileMap()
{
	top_unused_key = 0;
}


TileMap::~TileMap()
{
	for (std::map<unsigned short int, TILE>::iterator it = tiles.begin(); it != tiles.end(); it++)
		delete it->second.texture;
}


TILE TileMap::getTile(unsigned short int key) {
	if (top_unused_key <= key)
		return {"",NULL,0};
	return tiles[key];
}

void TileMap::add(std::string name, sf::Texture* texture, unsigned short int size) {
	tiles[top_unused_key] = {name,texture,size};
	top_unused_key++;
}

unsigned short int TileMap::getSize()
{
	return top_unused_key;
}
