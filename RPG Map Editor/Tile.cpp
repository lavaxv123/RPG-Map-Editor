#include "Tile.h"



Tile::Tile(std::string name, sf::Texture texture, unsigned int size)
{
	Tile::name = name;
	Tile::size = size;

}

Tile::Tile(std::string name, sf::Color color, unsigned int size)
{
	Tile::name = name;
	Tile::color = color;
	Tile::size = size;
}

Tile::~Tile()
{
}

void Tile::setFlag()
{
	
}