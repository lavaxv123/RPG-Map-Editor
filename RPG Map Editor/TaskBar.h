#ifndef TASKBAR_H
#define TASKBAR_H

#include "SFML\Graphics.hpp"
#include "FileHelper.h"
class TaskBar
{
public:
	TaskBar(sf::RenderWindow* window, FileHelper* fileHelper);
	~TaskBar();

	void render();
	void input();
	void renderButtons();
	bool isDropDownOpen();

private:

	bool isFileVisible;
	bool isToolsVisible;

	FileHelper* fileHelper;

	sf::RenderWindow* window;


	sf::RectangleShape* file;
	sf::RectangleShape* fileNew;
	sf::RectangleShape* saveMap;
	sf::RectangleShape* openMap;
	sf::RectangleShape* importSpritesheet;
	sf::RectangleShape* exitProgram;
	sf::RectangleShape* saveAs;

	sf::RectangleShape* tools;
	sf::RectangleShape* toolsPen;
	sf::RectangleShape* toolsFilledRect;
	sf::RectangleShape* toolsOuterRect;

	sf::Font arial;
};

#endif