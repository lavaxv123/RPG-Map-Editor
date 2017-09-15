#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TaskBar.h"
#include "TileMap.h"
#include "TileSelector.h"
#include "Grid.h"



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

	//Pointer to the tile map, used to convert tile hashes into textures
	TileMap* tileMap;

	TileSelector* tileSelector;
	Grid* grid;
	TaskBar* taskBar;
};

#endif