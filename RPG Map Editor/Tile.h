#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile(std::string name, sf::RenderTexture texture, unsigned int size);
	Tile(std::string name, sf::Color color);
	~Tile();
	void setFlag();
private:
	//Texture texture;
	unsigned int size;
	std::string name;
	sf::Color color;
	//byte flag
};

#endif