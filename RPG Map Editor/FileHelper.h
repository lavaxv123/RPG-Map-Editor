#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "SpriteSheet.h"
#include "Grid.h"

struct TEXT_BOX {
	sf::RectangleShape box;
	sf::Text text;
};

enum QUERY_TYPE {
	NEW, SAVE, SAVE_AS, EXIT
};

class FileHelper
{
public:
	FileHelper(Grid* grid, TileMap* tileMap);
	~FileHelper();
	bool loadMap();
	bool saveAs();
	bool save();
	bool importSpriteSheet();
	bool querySave();
	void queryNewGrid();
	bool openQuery(QUERY_TYPE q);

private:
	Grid* grid;
	TileMap* tileMap;
	std::string currentFile;
};

#endif