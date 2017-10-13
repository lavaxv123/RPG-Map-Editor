#include "Grid.h"
#include <stdlib.h>
#include <fstream>
#include <windows.h>

#define OFFSET .5f
#define LEFT_PANEL_SIZE 321.f
#define ZOOM_OFFSET .2f
#define TOP_BAR_SIZE 30.f
#define TICK_DELAY 150

Grid::Grid(sf::RenderWindow* window, TileMap* tileMap): zoom_index(1.0f), initialized(false), mouseMode(PEN), fillRectbool(false)
{
	Grid::window = window;
	Grid::tileMap = tileMap;
	grid = new sf::View(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, (float)window->getSize().x, (float)window->getSize().y));
	grid->setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0.f, 1.f, 1.f));
	original_size = grid->getSize();

	fillRectOutline = new sf::RectangleShape(sf::Vector2f(16, 16));;
	fillRectOutline->setOutlineColor(sf::Color::Red);
	fillRectOutline->setFillColor(sf::Color::Transparent);
	fillRectOutline->setOutlineThickness(1);
}


Grid::~Grid()
{
	delete grid;
	delete tile_ids;
	delete fillRectOutline;
}

void Grid::init(unsigned int grid_width, unsigned int grid_height, unsigned int tile_size)
{
	if (initialized)
		delete tile_ids;
	Grid::tile_size = tile_size;
	Grid::grid_width = grid_width;
	Grid::grid_height = grid_height;
	tile_ids = new TILE_ID[grid_height * grid_width];
	for (unsigned int i = 0; i <grid_width* grid_height; i++) {
		tile_ids[i] = { (unsigned short int) 0x0000,0 };
	}
	grid->reset(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, (float)window->getSize().x, (float)window->getSize().y));
	x_offset = 0;
	y_offset = 0;
	zoom_index = 1.0f;
	initialized = true;
}

void Grid::render()
{
	//Creates a view for the grid
	if (!initialized)
		return;
	grid->setSize(sf::Vector2f(window->getSize().x * zoom_index,window->getSize().y * zoom_index));
	grid->setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0.f, 1.f, 1.f));
	
	window->setView(*grid);

	
	for (unsigned int i = 0; i < grid_width * grid_height; i++) {
		sf::Sprite sprite;
		TILE tile = tileMap->getTile(tile_ids[i].TILE_HASH);
		sprite.setTexture(*(tile.texture));
		sprite.setScale(sf::Vector2f(tile_size / sprite.getLocalBounds().width, tile_size / sprite.getLocalBounds().height));
		sprite.setPosition((float)((i%grid_width) * tile_size), (float)((i / grid_width) * tile_size));
		window->draw(sprite);
	}	
	if (fillRectbool) {
		fillRectOutline->setSize(sf::Vector2f(tile_size, tile_size));
		window->draw(*fillRectOutline);
	}
}


void Grid::update(float delta) {
	window->setView(*grid);
	grid->move(OFFSET * x_offset * delta, OFFSET * y_offset * delta);
}


void Grid::input(unsigned short int key)
{
	x_offset = 0;
	y_offset = 0;
	//Moves the grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x_offset++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x_offset--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y_offset++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y_offset--;
	}

	window->setView(*grid);
	//Changes tiles on the grid
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (mouseMode) {
		case PEN:
			penMode(key);
			break;
		case FILLED_RECT:
			filledRectMode(key);
			break;
		}
	}
}


void Grid::zoom(float delta) {
	window->setView(*grid);
	if (zoom_index == 0)
		zoom_index = .2f;
	grid->setSize(grid->getSize() / zoom_index);
	
	//Can't not increase the size of the view any more without causing graphical glitches
	if (zoom_index == .2f && delta > 0) 
		return;

	zoom_index -= (delta*ZOOM_OFFSET);
	if (zoom_index < .2f)
		zoom_index = .2f;

	sf::Vector2f mouse_before_zoom = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	grid->setSize(grid->getSize() * zoom_index);
	window->setView(*grid);
	sf::Vector2f mouse_after_zoom = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	grid->move(mouse_before_zoom -mouse_after_zoom);
}

void Grid::setMouseMode(unsigned short int mode) {
	mouseMode = mode;
	fillRectbool = false;


	if (mode == PEN)
		std::cout << "Mouse mode set to Pen." << std::endl;
	else if (mode == FILLED_RECT)
		std::cout << "Mouse mode set to Filled Rectangle." << std::endl;
}

void Grid::penMode(unsigned short int key) {
	if (sf::Mouse::getPosition(*window).x > 321 && sf::Mouse::getPosition(*window).y > TOP_BAR_SIZE) {
		sf::Vector2f temp_v = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		sf::Vector2i w_v((int)temp_v.x, (int)temp_v.y);
		TILE tile = tileMap->getTile(key);
		if (w_v.x / tile_size >= 0 && w_v.y / tile_size >= 0 && w_v.x / tile_size < grid_width && w_v.y / tile_size < grid_height && w_v.x >= 0 && w_v.y >= 0) {
			tile_ids[(((w_v.y / tile_size) * grid_width) + (w_v.x / tile_size))].TILE_HASH = key;
		}
	}
}

void Grid::filledRectMode(unsigned short int key) {
	

	sf::Vector2i tlCorner;
	sf::Vector2i size; // length, height

	if (sf::Mouse::getPosition(*window).x > 321 && sf::Mouse::getPosition(*window).y > TOP_BAR_SIZE) {
		sf::Vector2f temp_v = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		sf::Vector2i w_v(floor(temp_v.x / tile_size), floor(temp_v.y / tile_size)*tile_size);
		TILE tile = tileMap->getTile(key);
		
		if (w_v.x / tile_size >= 0 && w_v.y / tile_size >= 0 && w_v.x / tile_size < grid_width && w_v.y / tile_size < grid_height && w_v.x >= 0 && w_v.y >= 0) {
			if (!fillRectbool) {
				c1 = sf::Vector2i(floor(temp_v.x / tile_size), floor(temp_v.y / tile_size));

				std::cout << "Corner 1 Selected at Position: " << c1.x << ", " << c1.y << std::endl;
				fillRectOutline->setPosition(c1.x*tile_size, c1.y*tile_size);
				fillRectbool = true;
				std::cout.flush();
				Sleep(TICK_DELAY);
				
			}
			else if (fillRectbool) {
				c2 = sf::Vector2i(floor(temp_v.x / tile_size), floor(temp_v.y / tile_size));
				std::cout << "Corner 2 Selected at Position: " << c2.x << ", " << c2.y << std::endl;

				if (c1.x >= c2.x) {
					tlCorner.x = c2.x;
					size.x = c1.x - c2.x + 1;
				}
				else {
					tlCorner.x = c1.x;
					size.x = c2.x - c1.x + 1;
				}
				if (c1.y >= c2.y) {
					tlCorner.y = c2.y;
					size.y = c1.y - c2.y + 1;
				}
				else {
					tlCorner.y = c1.y;
					size.y = c2.y - c1.y + 1;
				}

				for (unsigned int i = tlCorner.y; i < tlCorner.y + size.y; i++) {
					for (unsigned int j = tlCorner.x; j < tlCorner.x + size.x; j++) {
						tile_ids[i*grid_width + j].TILE_HASH = key;
					}
				}
				std::cout.flush();
				Sleep(TICK_DELAY);

				fillRectbool = false;
			}
			

		}
	}
}

TILE_ID* Grid::getTileIDs() {
	return tile_ids;
}

unsigned int Grid::getWidth() {
	return grid_width;
}

unsigned int Grid::getHeight() {
	return grid_height;
}

unsigned short int Grid::getTileSize() {
	return tile_size;
}

void Grid::setTiles(std::vector<unsigned short int> &vect) {
	int count = 0;
	for (std::vector<unsigned short int>::iterator it = vect.begin(); it != vect.end(); it++) {
		tile_ids[count] = { *it,0x00000000 };
		if (count >= grid_width * grid_height)
			std::cout << "ln 147 grid" << std::endl;
		count++;
	}
}


unsigned short int Grid::getMouseMode() {
	return mouseMode;
}