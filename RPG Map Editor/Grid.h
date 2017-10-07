#ifndef GRID_H
#define GRID_H

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

// Only Pen has been implemented
enum MOUSE_MODE {
	PEN, FILLED_RECT, OUTER_RECT, FILLED_CIRCLE, OUTER_CIRCLE, LINE, MOVE
};

class Grid
{
public:
	Grid(sf::RenderWindow* window,TileMap* tileMap);
	~Grid();

	void init(unsigned int grid_width, unsigned int grid_height, unsigned int tile_size);
	void init(std::string filePath);
	void render();
	void update(float delta);
	void input(unsigned short int key);
	void zoom(float delta);
	void setMouseMode(unsigned short int mode);
	void penMode(unsigned short int key);
	void filledRectMode();
	TILE_ID* getTileIDs();
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned short int getTileSize();
	unsigned short int getMouseMode();
private:
	sf::RenderWindow* window;
	TileMap* tileMap;

	//Holds the tile identifiers in the tile grid
	TILE_ID* tile_ids;

	sf::View* grid;

	bool initialized;
	sf::Vector2f original_size;
	float x_offset;
	float y_offset;
	float zoom_index;
	unsigned int grid_height;
	unsigned int grid_width;
	unsigned short int tile_size;
	unsigned short int mouseMode;
};

#endif