#ifndef TILEMAP_H
#define TILEMAP_H

#include <map>
#include <iostream>
#include <SFML\Graphics.hpp>
struct TILE {
	std::string name;
	sf::Texture texture;
	unsigned short int size;
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	TILE getTile(unsigned short int key);
	void add(std::string name, sf::Texture texture, unsigned short int size);
private:
	unsigned short int top_unused_key;
	std::map<unsigned short int, TILE> tiles;
};

#endif

