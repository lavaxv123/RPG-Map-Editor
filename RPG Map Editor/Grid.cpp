#include "Grid.h"
#include <stdlib.h>

#define OFFSET .5f
#define LEFT_PANEL_SIZE 321.f
#define ZOOM_OFFSET .2f
#define TOP_BAR_SIZE 30.f

Grid::Grid(sf::RenderWindow* window, TileMap* tileMap): zoom_index(1.0f),grid_height(100),grid_width(100), initialized(false)
{
	Grid::window = window;
	Grid::tileMap = tileMap;
	grid = new sf::View(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, (float)window->getSize().x, (float)window->getSize().y));
	grid->setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0.f, 1.f, 1.f));
	original_size = grid->getSize();
}


Grid::~Grid()
{
	delete grid;
	delete tile_ids;
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

	initialized = true;
}

void Grid::init(std::string filePath) {
	if (initialized)
		delete tile_ids;
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

	sf::Sprite sprite;
	for (unsigned int i = 0; i < grid_width * grid_height; i++) {
		TILE tile = tileMap->getTile(tile_ids[i].TILE_HASH);
		sprite.setTexture(*(tile.texture));
		sprite.setPosition((float)((i%grid_width) * tile_size), (float)((i / grid_width) * tile_size));
		window->draw(sprite);
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
		if (sf::Mouse::getPosition(*window).x > 321 && sf::Mouse::getPosition(*window).y > TOP_BAR_SIZE) {
			sf::Vector2f temp_v = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			sf::Vector2i w_v((int)temp_v.x, (int)temp_v.y);
			TILE tile = tileMap->getTile(key);
			if (w_v.x / tile_size >= 0 && w_v.y / tile_size >= 0 && w_v.x / tile_size < grid_width && w_v.y / tile_size < grid_height && w_v.x >= 0 && w_v.y >= 0) {
				tile_ids[(((w_v.y / tile_size) * grid_width) + (w_v.x / tile_size))].TILE_HASH = key;
			}
		}
	}
}


void Grid::zoom(float delta) {
	window->setView(*grid);
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
