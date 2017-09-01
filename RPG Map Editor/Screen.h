#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Screen
{
public:
	Screen(unsigned int width, unsigned int height,std::string title);
	~Screen();
	void load(std::string filepath);
	void render();
	void input();
	bool isOpen();
private:
	sf::RenderWindow window;
	bool isFullscreen;
	unsigned int width;
	unsigned int height;
	std::vector<Tile> tiles;

	//TODO: don't hard code these
	unsigned int grid_width = 100;
	unsigned int grid_height = 100;
	unsigned int tile_size = 16;
};

#endif