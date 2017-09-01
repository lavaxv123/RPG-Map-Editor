#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include "TileMap.h"

class SpriteSheet
{
public:
	SpriteSheet(TileMap* tileMap);
	~SpriteSheet();
	bool load(std::string spritesheet_path, std::string detail_path);
private:
	TileMap* tileMap;
};

#endif
