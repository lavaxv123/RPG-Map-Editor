#include "QueryWindow.h"
#include <thread>




QueryWindow::QueryWindow(): isBlocked(false)
{
}

QueryWindow::~QueryWindow()
{
}

struct TEXT_BOX {
	sf::RectangleShape box;
	sf::Text text;
};

TEXT_BOX getTextField(int font_size, int text_length) {
	TEXT_BOX text_box = { sf::RectangleShape(sf::Vector2f(text_length * font_size, font_size + (font_size/2)))
						, sf::Text() };
	text_box.text.setCharacterSize(font_size);
	text_box.box.setFillColor(sf::Color::Black);
	text_box.box.setOutlineThickness(3);

	return text_box;
}

void threadGridQuery(Grid* grid, QueryWindow* query)
{
	query->blockInput();
	sf::RenderWindow window(sf::VideoMode(600, 200), "Create a new map",sf::Style::Close | sf::Style::Titlebar);
	unsigned short int grid_width;
	unsigned short int grid_height;
	unsigned short int tile_size;
	sf::Font font;
	if (!font.loadFromFile("../Resources/arial.ttf"))
		std::cout << "Font failed to load" << std::endl;
	TEXT_BOX buttons[3] = { getTextField(18, 10),  getTextField(18, 10), getTextField(18, 10) };
	for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++) 
		buttons[i].text.setFont(font);
	
	int currentFocus = 0;
	while (window.isOpen()) {
		//Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered){
				if (isdigit(static_cast<char>(event.text.unicode))) {
					buttons[currentFocus].text.setString(buttons[currentFocus].text.getString() + event.text.unicode);
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) {
					sf::String str = buttons[currentFocus].text.getString();
					str = str.substring(0, str.getSize() - 1);
					buttons[currentFocus].text.setString(str);
				}
				if (event.key.code == sf::Keyboard::Tab)
					currentFocus = (currentFocus + 1) % 3;
				if (event.key.code == sf::Keyboard::Return){
					grid->init(stoi((std::string)buttons[2].text.getString()),
						stoi((std::string)buttons[1].text.getString()),
						stoi((std::string)buttons[0].text.getString()));
					window.close();
				}
			}
			
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			for(int i = 0; i < sizeof(buttons)/sizeof(TEXT_BOX);i++)
				if (buttons[i].box.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
					currentFocus = i;
			}

		
		
		//Render
		window.clear();

		
		for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++) {
			if (i == currentFocus)
				buttons[i].box.setOutlineColor(sf::Color(255, 0, 0));
			else
				buttons[i].box.setOutlineColor(sf::Color(255, 255, 0));
			buttons[i].box.setPosition(25 + (i*(buttons[i].box.getSize().x + 25)), 100);
			buttons[i].text.setPosition(25 + (i*(buttons[i].box.getSize().x + 25)), 100);
			window.draw(buttons[i].box);
			window.draw(buttons[i].text);
		}
			
		
		window.display();
	}
	query->unblockInput();
}

void QueryWindow::queryGrid(Grid* grid) {
	query = std::thread(threadGridQuery, grid, this);
	query.detach();
}

bool QueryWindow::isInputBlocked()
{
	return isBlocked;
}
void QueryWindow::blockInput()
{
	isBlocked = true;
}
void QueryWindow::unblockInput()
{
	isBlocked = false;
}