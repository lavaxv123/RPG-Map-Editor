#include "Screen.h"
#include <iostream>
#include "SpriteSheet.h"


Screen::Screen(unsigned int width, unsigned int height,std::string title): width(width), height(height), isFullscreen(false)
{
	window.create(sf::VideoMode(width, height), title);
	tileMap = new TileMap();
	tileSelector = new TileSelector(&window, tileMap);
	grid = new Grid(&window,tileMap);
	fileHelper = new FileHelper(grid, tileMap);
	taskBar = new TaskBar(&window, fileHelper);
	fileHelper->importSpriteSheet("../Resources/default_data.txt");
	grid->init(50, 50, 16);
	sf::RectangleShape shape(sf::Vector2f(1.f, 1.f));
	shape.getGlobalBounds().contains(sf::Vector2f(1.f, 1.f));
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

void Screen::update(float delta) {
	grid->update(delta);
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
				grid->zoom((float)event.mouseWheel.delta);
			}
			else if (sf::Mouse::getPosition(window).x <= 321) {
				if (event.mouseWheel.delta != 0) {
					if (tileSelector->checkPage(event.mouseWheel.delta / abs(event.mouseWheel.delta))) {
						tileSelector->changePage(event.mouseWheel.delta/abs(event.mouseWheel.delta));
					}
				}
			}
		}

		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			if (fileHelper->openQuery(EXIT))
				window.close();
		if (event.type == sf::Event::Resized) {
			width = window.getSize().x;
			height = window.getSize().y;
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y)));

		}
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				grid->setMouseMode(PEN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				grid->setMouseMode(FILLED_RECT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				grid->setMouseMode(OUTER_RECT);

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