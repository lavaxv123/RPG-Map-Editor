#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include <vector>
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

class Screen
{
public:
	/**
	Creates a sfml window with width, height, and title equal to the constructor params
	*/
	Screen(unsigned int width, unsigned int height,std::string title);
	~Screen();

	/**
	@params1 the file path for a spritesheet
	@params2 the file path for a text document that describes the spritesheet
	loads tiles from the spritesheet into a tile map
	*/
	void load(std::string spritesheet_path, std::string data_path);

	/**
	Renders grid and left tile selector bar
	*/
	void render();


	void update();

	/**
	Checks for input
	includes quitting, resizing, keyboard, and mouse presses
	*/
	void input();

	/**
	returns whether the window is open or closed, pressing the x button closes the window
	*/
	bool isOpen();
private:
	//The sfml window created by the screen constructor
	sf::RenderWindow window;

	//used to identify if the window is in fullscreen mode
	bool isFullscreen;

	//width and height of the sfml window
	unsigned int width;
	unsigned int height;

	//TODO: don't hard code this
	//Holds the tile identifiers in the tile grid
	TILE_ID tile_ids[10000];

	//Pointer to the tile map, used to convert tile hashes into textures
	TileMap* tileMap;
	
	//The offset of the grid, changed with arrow keys or wasd
	float x_offset = 0.f;
	float y_offset = 0.f;

	//TODO: implement the zoom feature
	//Holds the current zoom value of the grid
	float zoom = 1.f;


	//TODO: don't hard code these
	//tile_ids should be equal to grid_width * grid_height
	unsigned int grid_width = 100;
	unsigned int grid_height = 100;

	//standard tile size
	unsigned int tile_size = 16;


	//mouse button is currently down if true
	bool isMouseDown = false;
};

#endif