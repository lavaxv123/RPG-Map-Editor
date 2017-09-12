#include "Grid.h"
#include <stdlib.h>

#define OFFSET 10.f
#define LEFT_PANEL_SIZE 321.f
#define ZOOM_OFFSET .2f

Grid::Grid(sf::RenderWindow* window, TileMap* tileMap): x_offset(0),y_offset(0),zoom_index(1.0f),grid_height(100),grid_width(100),isMouseDown(false)
{
	Grid::window = window;
	Grid::tileMap = tileMap;
	tile_ids = (TILE_ID*)malloc((grid_height * grid_width) *sizeof(TILE_ID));

	for (int i = 0; i <grid_width* grid_height; i++) {
		tile_ids[i] = { (unsigned short int) 0x0004,0 };
	}
}


Grid::~Grid()
{
	free(tile_ids);
	delete tile_ids;
}

void Grid::render()
{
	//Creates a view for the grid
	sf::View grid(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, (float)window->getSize().x, (float)window->getSize().y));
	grid.setViewport(sf::FloatRect((LEFT_PANEL_SIZE / window->getSize().x), 0, 1.f, 1.f));
	grid.move(x_offset, y_offset);
	grid.zoom(zoom_index);
	window->setView(grid);

	sf::Sprite sprite;
	for (int i = 0; i < grid_width * grid_height; i++) {
		TILE tile = tileMap->getTile(tile_ids[i].TILE_HASH);
		sprite.setTexture(*(tile.texture));
		sprite.setPosition((float)((i%grid_width) * tile.size), (float)((i / grid_width) * tile.size));
		window->draw(sprite);
	}
}

void Grid::input()
{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y_offset -= OFFSET;
	}
}

void Grid::update(unsigned short int key)
{
	if (isMouseDown) {
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
	
void Grid::setMouseButton(bool isDown) {
	isMouseDown = isDown;
}

void Grid::zoom(float delta) {
	zoom_index -= delta * ZOOM_OFFSET;
	if (zoom_index <= ZOOM_OFFSET)
		zoom_index = ZOOM_OFFSET;
}
