#ifndef FILEHELPER_H
#define FILEHELPER_H
#include "Grid.h"
#include "TileMap.h"
#include "QueryWindow.h"
#include <string>

class FileHelper
{
public:
	FileHelper(Grid* grid, TileMap* tileMap, QueryWindow* query);
	~FileHelper();
	bool loadMap();
	bool saveMap();
	bool importSpriteSheet();
	void initGrid();
private:
	Grid* grid;
	TileMap* tileMap;
	QueryWindow* query;
};

#endif