#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>

class Screen
{
public:
	Screen(unsigned int width, unsigned int height,std::string title);
	~Screen();
	void load(std::string filepath);
	void render();
	void input();
	bool isOpen();
private:
	sf::RenderWindow window;
	bool isFullscreen;
	unsigned int width;
	unsigned int height;
};

#endif