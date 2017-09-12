#ifndef TILEMAP_H
#define TILEMAP_H

#include <map>
#include <iostream>
#include <SFML\Graphics.hpp>

/**
TILE struct holds a name, texture, and tile size
This class maps a tile hash value into a TILE struct
*/
struct TILE {
	std::string name;
	sf::Texture* texture;
	unsigned short int size;
};

class TileMap
{
public:
	//Sets top_unused_key to 0
	TileMap();
	/**
	deletes all TILE structs in the tiles map on deconstruction
	*/
	~TileMap();

	//Gets mapping in tiles with the associated key
	TILE getTile(unsigned short int key);

	//Return the top unused key.

	unsigned short int getSize();

	//adds a new TILE struct to the map
	void add(std::string name, sf::Texture* texture, unsigned short int size);

	//gets the size of the map
	unsigned short int getSize();
private:
	//Next key to be used
	unsigned short int top_unused_key;

	//Map that holds all loaded TILE structs
	std::map<unsigned short int, TILE> tiles;
};

#endif

