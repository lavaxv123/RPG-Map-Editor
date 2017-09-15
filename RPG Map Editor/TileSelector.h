#pragma once
#include <vector>
#include "TileMap.h"


class TileSelector
{
public:
	TileSelector(sf::RenderWindow* window, TileMap* tileMap);
	~TileSelector();

	void render();
	void update();
	void input();
	unsigned short int getSelected();

private:
	void renderSelectors();
	void renderButtons();

	sf::RenderWindow* window;

	sf::RectangleShape* next;
	sf::RectangleShape* previous;


	TileMap* tileMap;
	sf::Font arial;
	std::vector<sf::RectangleShape> shapes;

	unsigned short int maxPageNumber;
	unsigned int page_numbers;
	unsigned short int current_selected;
};

