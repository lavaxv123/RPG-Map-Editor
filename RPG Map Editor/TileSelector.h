#ifndef TILESELECTOR_H
#define TILESELECTOR_H
#include <vector>
#include "TileMap.h"


class TileSelector
{
public:
	TileSelector(sf::RenderWindow* window, TileMap* tileMap);
	~TileSelector();

	void render();
	void input();
	void changePage(int change);

	bool checkPage(int delta);
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

#endif