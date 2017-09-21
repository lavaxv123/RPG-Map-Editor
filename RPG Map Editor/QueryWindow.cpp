#include "QueryWindow.h"
#include <thread>




QueryWindow::QueryWindow(Grid* grid, sf::RenderWindow* window): grid(grid), window(window)
{
}

QueryWindow::~QueryWindow()
{
}

void input(sf::RenderWindow* window)
{
	
}

void update()
{

}

void render(sf::RenderWindow* window)
{

}


void queryGrid(QueryWindow* query)
{
}

void QueryWindow::start() {
	std::thread query = std::thread(queryGrid,this);
}

void QueryWindow::closeWindow()
{

}

void QueryWindow::renderSavePrompt()
{
	sf::RectangleShape savePrompt(sf::Vector2f(window->getSize().x/4, window->getSize().y/4));
	savePrompt.setPosition(window->getSize().x*(3 / 8), window->getSize().y*(3 / 8));
	savePrompt.setFillColor(sf::Color(255, 242, 226));
	savePrompt.setOutlineThickness(3);
	savePrompt.setOutlineColor(sf::Color(119, 119, 119));
	window->draw(savePrompt);
}