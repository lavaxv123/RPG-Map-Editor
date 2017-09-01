#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"


class Screen
{
public:
	Screen(unsigned int width, unsigned int height,std::string title);
	~Screen();
	void load(std::string spritesheet_path, std::string data_path);
	void render();
	void input();
	bool isOpen();
private:
	sf::RenderWindow window;
	bool isFullscreen;
	unsigned int width;
	unsigned int height;
	std::vector<TILE> tiles;
	TileMap* tileMap;
	
	float x_offset = 0.f;
	float y_offset = 0.f;
	float zoom = 1.f;
	//TODO: don't hard code these
	unsigned int grid_width = 100;
	unsigned int grid_height = 100;
	unsigned int tile_size = 16;
};

#endif