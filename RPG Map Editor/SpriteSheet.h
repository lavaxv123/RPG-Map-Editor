#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include "TileMap.h"

class SpriteSheet
{
public:
	//Just sets tileMap pointer equal to the tileMap in this constructor
	SpriteSheet(TileMap* tileMap);
	~SpriteSheet();

	bool parse(std::string txt_file);


	/**
	Uses text from detail_path text file to load individual sprites from spritesheet_path
	*/
	bool load(std::string spritesheet_path, std::string detail_path);
private:
	//Pointer to the tile map object which is needed for loading tiles
	TileMap* tileMap;
};

#endif
