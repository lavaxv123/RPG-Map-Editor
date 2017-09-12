#pragma once
#include "TileMap.h"

/**
each tile in the grid is contained as a tile_id which is a hash and a flag
The hash value is for looking up tile texture, name, and size
flag is used for setting whether the tile is an event, solid, interactive, etc.
*/
struct TILE_ID {
	unsigned short int TILE_HASH;
	char flag;
};

class Grid
{
public:
	Grid(sf::RenderWindow* window,TileMap* tileMap);
	~Grid();

	void render();
	void input(unsigned short int key);
	void zoom(float delta);
private:
	sf::RenderWindow* window;
	TileMap* tileMap;

	//Holds the tile identifiers in the tile grid
	TILE_ID* tile_ids;

	sf::View* grid;

	sf::Vector2f original_size;
	float x_offset;
	float y_offset;
	float zoom_index;
	unsigned int grid_height;
	unsigned int grid_width;
};

