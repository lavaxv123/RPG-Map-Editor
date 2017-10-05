#include "FileHelper.h"


FileHelper::FileHelper(Grid * grid, TileMap * tileMap)
{
	FileHelper::grid = grid;
	FileHelper::tileMap = tileMap;

}

FileHelper::~FileHelper() {
}

std::string getFileName(const std::string & prompt, const LPCSTR &filter) {
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lpstrFilter = filter;
	ofns.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();

	if (!GetOpenFileName(&ofns)) {
		std::cout << "Failed to open file" << std::endl;
		return "";
	}
	return buffer;
}

std::string getSaveFile(const std::string &prompt) {
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();
	ofns.lpstrFilter = "Text Files\0 *.txt";
	std::cout << ofns.lpstrFilter << std::endl;
	if (!GetSaveFileName(&ofns)) {
		std::cout << "No file was picked" << std::endl;
		return "";
	}
	std::string filePath(buffer);
	if (filePath.length() > 4 && filePath.substr(filePath.length() - 4, filePath.length()).compare(".txt") == 0) {
		std::cout << "End in txt" << std::endl;
		std::cout << filePath.substr(filePath.length() - 4, filePath.length()).compare(".txt") << std::endl;
		return filePath;
	}
	else {
		filePath += ".txt";
		return filePath;
	}
}

bool FileHelper::loadMap()
{
	std::string fileName = getFileName("Select the text file with map data", "PNG Files\0 *.png");
	if (fileName.length() == 0)
		return false;
	SpriteSheet sheet(tileMap);
	sheet.parse(fileName);
	return false;
}

bool FileHelper::saveAs()
{
	std::string savePath = getSaveFile("Where to should this map be saved?");
	if (savePath.length() == 0)
		return false;
	std::cout << "Saving file name: " << savePath << std::endl;
	std::ofstream outfile;
	outfile.open(savePath, std::ios::out | std::ios::trunc);
	TILE_ID* tiles = grid->getTileIDs();
	for (int y = 0; y < grid->getHeight(); y++) {
		for (int x = 0; x < grid->getWidth(); x++) {
			outfile << tiles[x + (y * grid->getWidth())].TILE_HASH << " ";
		}
		outfile << std::endl;
	}
	currentFile = savePath;
	outfile.close();
	return true;
}

bool FileHelper::save() {
	if (currentFile.compare("") == 0)
		return saveAs();
	else {
		std::cout << "Saving file name: " << currentFile << std::endl;
		std::ofstream outfile;
		outfile.open(currentFile, std::ios::out | std::ios::trunc);
		TILE_ID* tiles = grid->getTileIDs();
		for (int y = 0; y < grid->getHeight(); y++) {
			for (int x = 0; x < grid->getWidth(); x++) {
				outfile << tiles[x + (y * grid->getWidth())].TILE_HASH << " ";
			}
			outfile << std::endl;
		}
		outfile.close();
		return true;
	}
}

bool FileHelper::importSpriteSheet()
{
	std::string fileName = getFileName("Select the text file with spritesheet data", "Text Files\0 *.txt");
	if (fileName.length() == 0)
		return false;
	SpriteSheet sheet(tileMap);
	sheet.parse(fileName);
	return false;
}

TEXT_BOX getTextField(int font_size, int text_length) {
	TEXT_BOX text_box = { sf::RectangleShape(sf::Vector2f(text_length * font_size * 1.0f, font_size + (font_size / 2)* 1.0f))
		, sf::Text() };
	text_box.text.setCharacterSize(font_size);
	text_box.box.setFillColor(sf::Color::Black);
	text_box.box.setOutlineThickness(3);

	return text_box;
}

bool FileHelper::querySave() 
{
	sf::RenderWindow window(sf::VideoMode(600, 200), "Do you want to save?", sf::Style::Close | sf::Style::Titlebar);
	sf::Font font;
	if (!font.loadFromFile("../Resources/arial.ttf"))
		std::cout << "Font failed to load" << std::endl;
	TEXT_BOX buttons[3] = { getTextField(18, 10),  getTextField(18, 10), getTextField(18, 10) };
	for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++)
		buttons[i].text.setFont(font);
	buttons[0].text.setString("Yes");
	buttons[1].text.setString("No");
	buttons[2].text.setString("Cancel");
	int currentFocus = 0;
	while (window.isOpen()) {
		//Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window.close();
				return false;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Tab)
					currentFocus = (currentFocus + 1) % 3;
				if (event.key.code == sf::Keyboard::Return) {
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (buttons[0].box.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
					std::cout << "Save" << std::endl;
					return save();
				}
				else if (buttons[1].box.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
					std::cout << "Don't save" << std::endl;
					return true;
				}
				else if (buttons[2].box.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
					std::cout << "Cancel" << std::endl;
					return false;
				}
			}
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

	return false;
}

void FileHelper::queryNewGrid()
{
	sf::RenderWindow window(sf::VideoMode(600, 200), "Create a new map", sf::Style::Close | sf::Style::Titlebar);
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
			if (event.type == sf::Event::TextEntered) {
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
				if (event.key.code == sf::Keyboard::Return) {
					grid->init(stoi((std::string)buttons[2].text.getString()),
						stoi((std::string)buttons[1].text.getString()),
						stoi((std::string)buttons[0].text.getString()));
					currentFile = "";
					window.close();
				}
			}

		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++)
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
}

bool FileHelper::openQuery(QUERY_TYPE q) 
{
	switch (q) {
	case NEW:
		if (querySave()) {
			queryNewGrid();
		}
		break;
	case SAVE:
		save();
		break;
	case SAVE_AS:
		saveAs();
		break;
	case EXIT:
		return querySave();
	}
	
	return false;
}


