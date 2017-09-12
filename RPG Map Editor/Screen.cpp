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
	load("../Resources/SpriteSheet.png", "../Resources/SpriteSheet.txt");
	tileSelector = new TileSelector(&window, tileMap);
	grid = new Grid(&window,tileMap);
}


Screen::~Screen()
{
	delete tileMap;
	
}


void Screen::load(std::string spritesheet_path, std::string data_path) {

	//TODO: FIX THIS
	SpriteSheet sheet(tileMap);
	sheet.load(spritesheet_path, data_path);
}


void Screen::render() {


	window.clear();

	tileSelector->render();
	grid->render();

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
			grid->zoom(event.mouseWheel.delta);
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

	grid->input(tileSelector->getSelected());
}

bool Screen::isOpen() {
	return window.isOpen();
}