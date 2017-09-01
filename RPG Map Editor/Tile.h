#ifndef TILE_H
#define TILE_H

#include <string>
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(std::string name, sf::Texture texture, unsigned int size);
	Tile(std::string name, sf::Color color, unsigned int size);
	~Tile();
	void setFlag();
private:
	sf::Texture texture;
	unsigned int size;
	std::string name;
	sf::Color color;
	//byte flag
};

#endif