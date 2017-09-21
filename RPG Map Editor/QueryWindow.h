#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include "Grid.h"
#include <thread>

class QueryWindow
{
public:
	QueryWindow(Grid* grid, sf::RenderWindow* window);
	~QueryWindow();

	void start();
	void closeWindow();
	void renderSavePrompt();

private:

	sf::RenderWindow* window;
	Grid* grid;
	std::thread query;
	unsigned short int tile_size;
	unsigned short int grid_width;
	unsigned short int grid_height;
};

#endif