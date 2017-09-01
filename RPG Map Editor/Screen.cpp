#include "Screen.h"



Screen::Screen(unsigned int width, unsigned int height,std::string title)
{
	Screen::width = width;
	Screen::height = height;
	window.create(sf::VideoMode(width, height), title);
	isFullscreen = false;
}


Screen::~Screen()
{
}


void Screen::load(std::string filepath) {
	
}


sf::RectangleShape createTileBox(unsigned int width, unsigned int height, sf::Color color, sf::Color outlineColor) {
	sf::RectangleShape tile(sf::Vector2f(width, height));
	tile.setFillColor(color);
	tile.setOutlineThickness(2);
	tile.setOutlineColor(outlineColor);
	return tile;
}

void Screen::render() {


	window.clear();
	sf::RectangleShape tileViewer(sf::Vector2f(304, window.getSize().y - 20));
	tileViewer.setFillColor(sf::Color(255, 242, 226));
	tileViewer.setOutlineThickness(3);
	tileViewer.setOutlineColor(sf::Color(119, 119, 119));

	tileViewer.setPosition(10, 10);
	window.draw(tileViewer);

	//Renders sections within tile viewer
	for (unsigned int i = 25; i < height - 100; i += 100) {
		sf::RectangleShape tile = createTileBox(274, 75, sf::Color(255, 255, 255), sf::Color(0, 0, 0));
		tile.setPosition(25, i);
		window.draw(tile);
	}

	window.display();
}



void Screen::input() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
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
		if (event.type == sf::Event::Resized) {
			width = window.getSize().x;
			height = window.getSize().y;
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
		}

	}
}

bool Screen::isOpen() {
	return window.isOpen();
}