#include "Screen.h"
#include <iostream>
#include "SpriteSheet.h"


Screen::Screen(unsigned int width, unsigned int height,std::string title)
{
	Screen::width = width;
	Screen::height = height;
	window.create(sf::VideoMode(width, height), title);
	window.setFramerateLimit(60);
	isFullscreen = false;
	tileMap = new TileMap();
	SpriteSheet sheet(tileMap);
	sheet.parse("../Resources/default_data.txt");
	tileSelector = new TileSelector(&window, tileMap);
	grid = new Grid(&window,tileMap);
	fileHelper = new FileHelper(grid, tileMap);
	taskBar = new TaskBar(&window, fileHelper);

}


Screen::~Screen()
{
	delete tileMap;
	delete tileSelector;
	delete grid;
	delete taskBar;
	delete fileHelper;
}



void Screen::render() {


	window.clear();
	
	
	tileSelector->render();
	grid->render();
	taskBar->render();
	

	window.display();
}

void Screen::update() {
	
}


void Screen::input() {

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed) {
			if (sf::Mouse::getPosition(window).x <= 321) {
				tileSelector->input();
			}
		}
		if (event.type == sf::Event::MouseWheelMoved) {
			if (sf::Mouse::getPosition(window).x > 321 && sf::Mouse::getPosition(window).y > 30) {
				grid->zoom(event.mouseWheel.delta);
			}

		}

		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
		
		
		if (event.type == sf::Event::Resized) {
			width = window.getSize().x;
			height = window.getSize().y;
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
		}
	}
	// Enter FullScreen
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && isFullscreen == false) {
		window.create(sf::VideoMode().getDesktopMode(), "My Window", sf::Style::Fullscreen);
		isFullscreen = true;
	}
	// Leave FullScreen
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) && isFullscreen == true) {
		window.create(sf::VideoMode(width, height), "My window");
		isFullscreen = false;
	}
	if (!taskBar->isDropDownOpen()) {
		grid->input(tileSelector->getSelected());
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		taskBar->input();
	}
	
}

bool Screen::isOpen() {
	return window.isOpen();
}