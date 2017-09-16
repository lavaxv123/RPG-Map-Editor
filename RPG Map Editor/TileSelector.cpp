#include "TileSelector.h"



TileSelector::TileSelector(sf::RenderWindow* window, TileMap* tileMap)
{
	TileSelector::window = window;
	TileSelector::tileMap = tileMap;
	arial.loadFromFile("../Resources/arial.ttf");
	
	next = new sf::RectangleShape(sf::Vector2f(60, 20));
	previous = new sf::RectangleShape(sf::Vector2f(62, 20));


	page_numbers = 0;

}


TileSelector::~TileSelector()
{
	delete next;
	delete previous;

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
		if ((i / 100) + (((window->getSize().y - 25) / 100)* page_numbers) == current_selected)
			tile.setOutlineColor(sf::Color(255, 0, 0));
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

	//Finds the maximum number of pages for the Tile Viewer
	maxPageNumber = ((100 * tileMap->getSize())/(window->getSize().y - 100));
}


void TileSelector::renderButtons() {
	//Render buttons
	//Render next button
	next->setFillColor(sf::Color(255, 242, 226));
	next->setOutlineThickness(1);
	next->setOutlineColor(sf::Color(119, 119, 119));
	next->setPosition(244, (float)(window->getSize().y - 40));

	sf::Text nextTXT("Next", arial, 16);
	nextTXT.setPosition(255, (float)(window->getSize().y - 40));
	nextTXT.setFillColor(sf::Color(0, 0, 0));

	window->draw(*next);
	window->draw(nextTXT);

	//Render previous button
	previous->setFillColor(sf::Color(255, 242, 226));
	previous->setOutlineThickness(1);
	previous->setOutlineColor(sf::Color(119, 119, 119));
	previous->setPosition(20, (float)(window->getSize().y - 40));

	sf::Text previousTXT("Previous", arial, 16);
	previousTXT.setPosition(20, (float)(window->getSize().y - 40));
	previousTXT.setFillColor(sf::Color(0, 0, 0));

	window->draw(*previous);
	window->draw(previousTXT);


}


void TileSelector::render()
{
	//Sets view for rendering tile selector
	sf::View tileView(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	tileView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	window->setView(tileView);

	//Renders tile selector rectangle
	sf::RectangleShape tileViewer(sf::Vector2f(315, (float)(window->getSize().y - 6)));
	tileViewer.setFillColor(sf::Color(255, 242, 226));
	tileViewer.setOutlineThickness(3);
	tileViewer.setOutlineColor(sf::Color(119, 119, 119));
	tileViewer.setPosition(3, 3);
	window->draw(tileViewer);

	//Render the page numbers at the bottom
	sf::Text pageNumberTXT("", arial, 16);
	pageNumberTXT.setString("Page: " + std::to_string(page_numbers + 1) + " of " + std::to_string(maxPageNumber + 1));
	pageNumberTXT.setPosition(100, (float)(window->getSize().y - 40));
	pageNumberTXT.setFillColor(sf::Color(0, 0, 0));
	window->draw(pageNumberTXT);

	//Renders individual selectors
	renderSelectors();

	//Renders all buttons
	renderButtons();

	if (page_numbers > maxPageNumber)
		page_numbers = maxPageNumber;

}

void TileSelector::update()
{
}

void TileSelector::input()
{
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (next->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))) {
		if (page_numbers < maxPageNumber) {
			page_numbers++;
			std::cout << page_numbers << std::endl;
		}

	}
	else if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && previous->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
		if (page_numbers > 0) {
			page_numbers--;
			std::cout << page_numbers << std::endl;
		}

	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*window).x <= 321) {
		for (unsigned int i = 25; i < window->getSize().y - 100; i += 100) {
			sf::RectangleShape tile(sf::Vector2f(274, 75));
			tile.setFillColor(sf::Color(255, 255, 255));
			tile.setOutlineThickness(2);
			tile.setOutlineColor(sf::Color(0, 0, 0));
			tile.setPosition(25, (float)i);

			if (tile.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
				unsigned short int clicked_key = (i / 100) + (page_numbers * ((window->getSize().y - 125) / 100)) + page_numbers;
				std::cout << "Clicked key: " << clicked_key << std::endl;
				if (clicked_key < tileMap->getSize()) {
					current_selected = clicked_key;
				}
			}
		}
	}
}

void TileSelector::changePage(int change)
{
	page_numbers += change;
}

bool TileSelector::checkPage(int delta)
{
	if (page_numbers == maxPageNumber && delta == -1) {
		std::cout << delta << std::endl;
		return true;
	}
	else if (page_numbers == 0 && delta == 1) {
		std::cout << delta << std::endl;
		return true;
	}
	else if (0 < page_numbers && page_numbers < maxPageNumber) {
		return true;
	}
	else
		return false;
}

unsigned short int TileSelector::getSelected()
{
	return current_selected;
}
