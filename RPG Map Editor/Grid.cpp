#include "Grid.h"
#include <stdlib.h>

#define OFFSET 15.f
#define LEFT_PANEL_SIZE 321.f
#define ZOOM_OFFSET .2f

Grid::Grid(sf::RenderWindow* window, TileMap* tileMap): x_offset(0.f),y_offset(0.f),zoom_index(1.0f),grid_height(100),grid_width(100)
{
	Grid::window = window;
	Grid::tileMap = tileMap;
	tile_ids = (TILE_ID*)malloc((grid_height * grid_width) *sizeof(TILE_ID));
	grid = new sf::View(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, (float)window->getSize().x, (float)window->getSize().y));
	grid->setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, 1.f, 1.f));
	original_size = grid->getSize();
	for (unsigned int i = 0; i <grid_width* grid_height; i++) {
		tile_ids[i] = { (unsigned short int) 0x0004,0 };
	}
}


Grid::~Grid()
{
	delete grid;
	free(tile_ids);
	delete tile_ids;
}

void Grid::render()
{
	//Creates a view for the grid
	
	grid->setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, 1.f, 1.f));
	window->setView(*grid);

	sf::Sprite sprite;
	for (unsigned int i = 0; i < grid_width * grid_height; i++) {
		TILE tile = tileMap->getTile(tile_ids[i].TILE_HASH);
		sprite.setTexture(*(tile.texture));
		sprite.setPosition((float)((i%grid_width) * tile.size), (float)((i / grid_width) * tile.size));
		window->draw(sprite);
	}
}

void Grid::input(unsigned short int key)
{
	//Moves the grid
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		grid->move(OFFSET, 0.f);
		x_offset += OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		grid->move(-OFFSET, 0.f);
		x_offset -= OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		grid->move(0.f, OFFSET);
		y_offset += OFFSET;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		grid->move(0.f, -OFFSET);
		y_offset -= OFFSET;
	}

	//Changes tiles on the grid
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (sf::Mouse::getPosition(*window).x > 321) {
			sf::Vector2f temp_v = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			sf::Vector2i w_v((int)temp_v.x, (int)temp_v.y);
			TILE tile = tileMap->getTile(key);
			if (w_v.x / tile.size >= 0 && w_v.y / tile.size >= 0 && w_v.x / tile.size < grid_width && w_v.y / tile.size < grid_height && w_v.x >= 0 && w_v.y >= 0) {
				tile_ids[(((w_v.y / tile.size) * grid_width) + (w_v.x / tile.size))].TILE_HASH = key;
			}
		}
	}
}


void Grid::zoom(float delta) {
	zoom_index += (delta*ZOOM_OFFSET);

	grid->setSize(original_size * zoom_index);
	grid->move(-x_offset, -y_offset);
}
