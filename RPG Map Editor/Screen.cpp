#include "Screen.h"
#include <iostream>
#include "SpriteSheet.h"

#define OFFSET 5.f

Screen::Screen(unsigned int width, unsigned int height,std::string title)
{
	Screen::width = width;
	Screen::height = height;
	window.create(sf::VideoMode(width, height), title);
	window.setFramerateLimit(60);
	isFullscreen = false;
	tileMap = new TileMap();
	next = new sf::RectangleShape(sf::Vector2f(60, 20));
	previous = new sf::RectangleShape(sf::Vector2f(62, 20));
	load("../Resources/SpriteSheet.png", "../Resources/SpriteSheet.txt");
	arial.loadFromFile("../Resources/arial.ttf");
}


Screen::~Screen()
{
	delete tileMap;
	delete next;
	delete previous;
}


void Screen::load(std::string spritesheet_path, std::string data_path) {

	//TODO: FIX THIS
	SpriteSheet sheet(tileMap);
	sheet.load(spritesheet_path, data_path);
	std::cout << (tileMap->getTile(0)).name << std::endl;
	for(int i = 0; i <sizeof(tile_ids)/sizeof(TILE_ID); i++){
		tile_ids[i] = { (unsigned short int) 0x0004,0};
	}
}


sf::RectangleShape createTileBox(unsigned int width, unsigned int height, sf::Color color, sf::Color outlineColor) {
	sf::RectangleShape tile(sf::Vector2f((float)width,(float)height));
	tile.setFillColor(color);
	tile.setOutlineThickness(2);
	tile.setOutlineColor(outlineColor);
	return tile;
}

void Screen::render() {


	window.clear();
	sf::View tileView(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y));
	tileView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::RectangleShape tileViewer(sf::Vector2f(304, (float)(window.getSize().y - 20)));
	tileViewer.setFillColor(sf::Color(255, 242, 226));
	tileViewer.setOutlineThickness(3);
	tileViewer.setOutlineColor(sf::Color(119, 119, 119));

	tileViewer.setPosition(10, 10);
	window.setView(tileView);
	window.draw(tileViewer);


	//Left and Right arrow buttons to swap through textures
	next->setFillColor(sf::Color(255, 242, 226));
	next->setOutlineThickness(1);
	next->setOutlineColor(sf::Color(119, 119, 119));
	next->setPosition(244, (float)(window.getSize().y - 40));

	sf::Text nextTXT("Next", arial, 16);
	nextTXT.setPosition(255, (float)(window.getSize().y - 40));
	nextTXT.setFillColor(sf::Color(0, 0, 0));
	
	
	previous->setFillColor(sf::Color(255, 242, 226));
	previous->setOutlineThickness(1);
	previous->setOutlineColor(sf::Color(119, 119, 119));
	previous->setPosition(20, (float)(window.getSize().y - 40));

	sf::Text previousTXT("Previous", arial, 16);
	previousTXT.setPosition(20, (float)(window.getSize().y - 40));
	previousTXT.setFillColor(sf::Color(0, 0, 0));

	window.draw(*next);
	window.draw(nextTXT);
	window.draw(*previous);
	window.draw(previousTXT);

	//Renders sections within tile viewer
	for (unsigned int i = 25; i < height - 100; i += 100) {
		sf::RectangleShape tile = createTileBox(274, 75, sf::Color(255, 255, 255), sf::Color(0, 0, 0));
		tile.setPosition(25, (float)i);
		sf::Sprite tile_sprite;
		TILE tile_w_texture = tileMap->getTile((i / 100) + (((height - 25)/100)* pageNum));
		if (tile_w_texture.size == 0)
			break;
		tile_sprite.setTexture(*tile_w_texture.texture);
		tile_sprite.scale(sf::Vector2f(4.0f, 4.0f));
		tile_sprite.setPosition(30, (float)(i + 4));
		
		sf::Text text;
		text.setFont(arial);
		text.setString(tile_w_texture.name);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(0, 0, 0));
		text.setPosition(100, (float)(i + 4));
		window.draw(tile);
		window.draw(tile_sprite);
		window.draw(text);
	}
	sf::View grid(sf::FloatRect((316.0f / window.getSize().x), 0, (float)window.getSize().x, (float)window.getSize().y));
	grid.setViewport(sf::FloatRect((321.f / window.getSize().x), 0, 1.f, 1.f));
	grid.move(x_offset, y_offset);
	grid.zoom(zoom);
	window.setView(grid);

	sf::Sprite sprite;
	for (int i = 0; i < sizeof(tile_ids) / sizeof(TILE_ID); i++) {
		sprite.setTexture(*(tileMap->getTile(tile_ids[i].TILE_HASH).texture));
		sprite.setPosition((float)((i%grid_width) * tile_size), (float)((i/grid_width) * 16));
		window.draw(sprite);
	}
	
	window.display();
}

void Screen::update() {
	if (isMouseDown) {
		if (sf::Mouse::getPosition(window).x > 321) {
			sf::Vector2f temp_v = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			sf::Vector2i w_v((int)temp_v.x, (int)temp_v.y);
			if (w_v.x/tile_size >= 0 && w_v.y/tile_size >= 0 && w_v.x/tile_size < grid_width && w_v.y/tile_size < grid_height && w_v.x >= 0 && w_v.y >= 0) {
				tile_ids[(((w_v.y/tile_size) * grid_width) + (w_v.x/tile_size))].TILE_HASH = 1;
			}
		}
	}
}


void Screen::input() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed) {
			isMouseDown = true;
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			isMouseDown = false;
		}
		if (event.type == sf::Event::MouseWheelMoved) {
			
			zoom -= event.mouseWheel.delta * .2f;
			zoom = zoom < .2f ? .2f: zoom;
		}

		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
		
		
		if (event.type == sf::Event::Resized) {
			width = window.getSize().x;
			height = window.getSize().y;
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));
		}
		
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (next->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))) {
			pageNum++;
			std::cout << pageNum << std::endl;
		}
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && previous->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
			pageNum--;
			std::cout << pageNum << std::endl;
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
		x_offset += OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x_offset -= OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y_offset += OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)	|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y_offset -= OFFSET;
	}


}

bool Screen::isOpen() {
	return window.isOpen();
}