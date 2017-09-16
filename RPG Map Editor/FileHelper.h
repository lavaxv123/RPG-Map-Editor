#ifndef FILEHELPER_H
#define FILEHELPER_H
#include "Grid.h"
#include "TileMap.h"
#include <string>

class FileHelper
{
public:
	FileHelper(Grid* grid, TileMap* tileMap);
	~FileHelper();
	bool loadMap();
	bool saveMap();
	bool importSpriteSheet();
private:
	Grid* grid;
	TileMap* tileMap;
};

#endif