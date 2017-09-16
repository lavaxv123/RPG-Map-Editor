#include "TaskBar.h"

#define LEFT_PANEL_SIZE 321.f
#define TASK_BAR_SIZE 30.f

TaskBar::TaskBar(sf::RenderWindow* window)
{
	file = new sf::RectangleShape(sf::Vector2f(60, 22));
	taskBarView = new sf::View(sf::FloatRect(0, LEFT_PANEL_SIZE/(float)window->getSize().y, (float)window->getSize().x, 30.f));

	TaskBar::window = window;
}


TaskBar::~TaskBar()
{
	delete file;
	delete taskBarView;
}

void TaskBar::render()
{

	//Sets view for rendering task bar
	taskBarView->setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
	window->setView(*taskBarView);



	//Renders the bar at the top of the screen

	sf::RectangleShape taskBar(sf::Vector2f((float)(window->getSize().x - 324), 24));
	taskBar.setFillColor(sf::Color(255, 242, 226));
	taskBar.setOutlineThickness(3);
	taskBar.setOutlineColor(sf::Color(119, 119, 119));
	taskBar.setPosition(321, 3);
	window->draw(taskBar);

	renderButtons();
}

void TaskBar::renderButtons()
{
	//Render file button
	file->setFillColor(sf::Color(219, 208, 171));
	file->setOutlineThickness(1);
	file->setOutlineColor(sf::Color(110, 110, 110));
	file->setPosition(321, 4);

	sf::Text fileTXT("File", arial, 16);
	fileTXT.setPosition(323, 4);
	fileTXT.setFillColor(sf::Color(0, 0, 0));

	window->draw(*file);
	window->draw(fileTXT);
}

void TaskBar::input()
{

}