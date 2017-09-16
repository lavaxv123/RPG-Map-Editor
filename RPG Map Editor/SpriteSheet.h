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

	/**
	Uses text from detail_path text file to load individual sprites
	@return error
	*/
	bool parse(std::string txt_file);


	
private:
	//Pointer to the tile map object which is needed for loading tiles
	TileMap* tileMap;
};

#endif
