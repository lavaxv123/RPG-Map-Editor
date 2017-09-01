#include <SFML\Graphics.hpp>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

void render(sf::RenderWindow* window) {
	window->clear();
	sf::RectangleShape tileHolder(sf::Vector2f(304, window->getSize().y - 20));
	tileHolder.setFillColor(sf::Color(100, 250, 50));
	tileHolder.setPosition(10, 10);
	window->draw(tileHolder);
	window->display();
}


int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH , HEIGHT), "My window");
	
	
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
			// Enter FullScreen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) 
				window.create(sf::VideoMode().getDesktopMode(), "My Window",sf::Style::Fullscreen);
			// Leave FullScreen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
				window.create(sf::VideoMode(WIDTH, HEIGHT), "My window");
			if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0.f,0.f,window.getSize().x,window.getSize().y)));
			
        }
		
		render(&window);

		
		
    }

    return 0;
}