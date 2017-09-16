#ifndef TASKBAR_H
#define TASKBAR_H

#include "SFML\Graphics.hpp"

class TaskBar
{
public:
	TaskBar(sf::RenderWindow* window);
	~TaskBar();

	void render();
	void input();
	void renderButtons();
	bool isDropDownOpen();

private:

	bool isFileVisible;

	sf::RenderWindow* window;

	sf::RectangleShape* file;
	sf::RectangleShape* saveMap;
	sf::RectangleShape* openMap;
	sf::RectangleShape* importSpritesheet;


	sf::Font arial;
};

#endif