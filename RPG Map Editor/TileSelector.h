#pragma once
#include "Screen.h"

class TileSelector
{
public:
	TileSelector(sf::RenderWindow* window, TileMap* tileMap);
	~TileSelector();

	void render();
	void update();
	void input();
private:
	void renderSelectors();
	sf::RenderWindow* window;
	TileMap* tileMap;
	sf::Font arial;

	unsigned int page_numbers;
};

