#ifndef TASKBAR_H
#define TASKBAR_H

#include "Screen.h"

class TaskBar
{
public:
	TaskBar(sf::RenderWindow* window);
	~TaskBar();

	void render();
	void input();
	void renderButtons();

private:

	sf::RenderWindow* window;

	sf::RectangleShape* file;

	sf::Font arial;
};

#endif