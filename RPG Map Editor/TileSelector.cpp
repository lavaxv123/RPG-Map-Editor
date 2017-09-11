#include "TileSelector.h"



TileSelector::TileSelector(sf::RenderWindow* window, TileMap* tileMap)
{
	TileSelector::window = window;
	TileSelector::tileMap = tileMap;
	arial.loadFromFile("../Resources/arial.ttf");

	page_numbers = 0;
}


TileSelector::~TileSelector()
{
}


void TileSelector::renderSelectors()
{
	//Renders sections within tile viewer
	for (unsigned int i = 25; i < window->getSize().y - 100; i += 100) {
		sf::RectangleShape tile(sf::Vector2f(274, 75));
		tile.setFillColor(sf::Color(255, 255, 255));
		tile.setOutlineThickness(2);
		tile.setOutlineColor(sf::Color(0, 0, 0));
		tile.setPosition(25, (float)i);


		TILE tile_w_texture = tileMap->getTile((i / 100) + (((window->getSize().y - 25) / 100)* page_numbers));
		if (tile_w_texture.size == 0)
			break;

		sf::Sprite tile_sprite;
		tile_sprite.setTexture(*tile_w_texture.texture);
		tile_sprite.scale(sf::Vector2f(4.0f, 4.0f));
		tile_sprite.setPosition(30, (float)(i + 4));

		sf::Text text;
		text.setFont(arial);
		text.setString(tile_w_texture.name);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(0, 0, 0));
		text.setPosition(100, (float)(i + 4));

		window->draw(tile);
		window->draw(tile_sprite);
		window->draw(text);
	}
}


void TileSelector::render()
{
	//Sets view for rendering tile selector
	sf::View tileView(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	tileView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	//Renders tile selector rectangle
	sf::RectangleShape tileViewer(sf::Vector2f(304, (float)(window->getSize().y - 20)));
		tileViewer.setFillColor(sf::Color(255, 242, 226));
		tileViewer.setOutlineThickness(3);
		tileViewer.setOutlineColor(sf::Color(119, 119, 119));
		tileViewer.setPosition(10, 10);

	//Renders individual selectors
	renderSelectors();
	
}

void TileSelector::update()
{
}

void TileSelector::input()
{
}

