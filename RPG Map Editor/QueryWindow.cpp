#include "QueryWindow.h"
#include <thread>




QueryWindow::QueryWindow(Grid* grid): grid(grid)
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

