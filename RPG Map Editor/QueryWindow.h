#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include "Grid.h"
#include <thread>

class QueryWindow
{
public:
	QueryWindow();
	~QueryWindow();
	void queryGrid(Grid* grid);
	bool isInputBlocked();
	void blockInput();
	void unblockInput();
	void querySave(Grid* grid);

private:
	bool isBlocked;
	std::thread query;
	unsigned short int tile_size;
	unsigned short int grid_width;
	unsigned short int grid_height;
};

#endif