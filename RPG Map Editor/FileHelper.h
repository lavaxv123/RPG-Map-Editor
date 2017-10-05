#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <SFML\Graphics.hpp>
#include <string>
#include <thread>
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
	NEW, SAVE
};

class FileHelper
{
public:
	FileHelper(Grid* grid, TileMap* tileMap);
	~FileHelper();
	bool loadMap();
	bool saveMap();
	bool importSpriteSheet();
	bool querySave();
	void queryNewGrid();
	void openQuery(QUERY_TYPE q);
	bool isInputBlocked();

private:
	Grid* grid;
	TileMap* tileMap;

	std::thread query;

	bool isBlocked;
};

#endif