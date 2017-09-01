#include "TileMap.h"



TileMap::TileMap()
{
	top_unused_key = 0;
}


TileMap::~TileMap()
{
}


TILE TileMap::getTile(unsigned short int key) {
	return tiles[key];
}

void TileMap::add(std::string name, sf::Texture texture, unsigned short int size) {
	tiles[top_unused_key] = {name,texture,size};
	top_unused_key++;
}