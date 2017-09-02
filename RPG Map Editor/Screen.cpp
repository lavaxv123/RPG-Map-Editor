#include "Screen.h"
#include <iostream>
#include "SpriteSheet.h"
#include <array>

Screen::Screen(unsigned int width, unsigned int height,std::string title)
{
	Screen::width = width;
	Screen::height = height;
	window.create(sf::VideoMode(width, height), title);
	window.setFramerateLimit(60);
	isFullscreen = false;
	tileMap = new TileMap();
	load("../Resources/SpriteSheet.png", "../Resources/SpriteSheet.txt");
}


Screen::~Screen()
{
	delete tileMap;

}


void Screen::load(std::string spritesheet_path, std::string data_path) {

	//TODO: FIX THIS
	SpriteSheet sheet(tileMap);
	sheet.load(spritesheet_path, data_path);
	std::cout << (tileMap->getTile(0)).name << std::endl;
	for(int i = 0; i <sizeof(tile_ids)/sizeof(TILE_ID); i++){
		tile_ids[i] = { (unsigned short int) 0x0000,'0' };
	}
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
	sf::View tileView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	tileView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::RectangleShape tileViewer(sf::Vector2f(304, window.getSize().y - 20));
	tileViewer.setFillColor(sf::Color(255, 242, 226));
	tileViewer.setOutlineThickness(3);
	tileViewer.setOutlineColor(sf::Color(119, 119, 119));

	tileViewer.setPosition(10, 10);
	window.setView(tileView);
	window.draw(tileViewer);

	//Renders sections within tile viewer
	for (unsigned int i = 25; i < height - 100; i += 100) {
		sf::RectangleShape tile = createTileBox(274, 75, sf::Color(255, 255, 255), sf::Color(0, 0, 0));
		tile.setPosition(25, i);
		window.draw(tile);
	}
	sf::View grid(sf::FloatRect((316.0f / window.getSize().x), 0, window.getSize().x, window.getSize().y));
	grid.setViewport(sf::FloatRect((316.f / window.getSize().x), 0, 1.f, 1.f));
	grid.move(x_offset, y_offset);
	grid.zoom(1.f);
	window.setView(grid);

	sf::Sprite sprite;
	for (int i = 0; i < sizeof(tile_ids) / sizeof(TILE_ID); i++) {
		sprite.setTexture(*(tileMap->getTile(tile_ids[i].TILE_HASH).texture));
		sprite.setPosition((i%100) * 16, (i/100) * 16);
		window.draw(sprite);
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
	//Moves the grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x_offset -= 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x_offset += 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y_offset -= 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)	|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y_offset += 2.f;
	}
}

bool Screen::isOpen() {
	return window.isOpen();
}