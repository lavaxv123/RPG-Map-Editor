#include "FileHelper.h"


FileHelper::FileHelper(Grid * grid, TileMap * tileMap)
{
	FileHelper::grid = grid;
	FileHelper::tileMap = tileMap;

}

FileHelper::~FileHelper() {
}

std::string getFileName(const std::string & prompt) {
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lpstrFilter = "Text Files\0 *.txt";
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
	/*
	std::string fileName = getFileName("Select the text file with map data");
	if (fileName.length() == 0)
		return false;
	SpriteSheet sheet(tileMap);
	sheet.parse(fileName);
	return false;
	*/
	std::ifstream infile;

	return true;
}

void FileHelper::saveData(std::string savePath) {
	std::ofstream outfile;
	outfile.open(savePath, std::ios::out | std::ios::trunc);
	outfile << "$DETAIL" << std::endl;
	outfile << '{' << std::endl;
	outfile << "SIZE "  <<grid->getTileSize() << std::endl;
	outfile << '}' << std::endl;
	outfile << std::endl;
	outfile << "$DATA" << std::endl;
	outfile << '{' << std::endl;
	for (std::vector<std::string>::iterator it = spritesheet_vect.begin(); it != spritesheet_vect.end(); it++)
		outfile << *it << std::endl;

	outfile << '}' << std::endl;
	outfile << std::endl;
	outfile << "$SPRITES" << std::endl;
	outfile << '{' << std::endl;
	TILE_ID* tiles = grid->getTileIDs();
	//Create a list of unique tiles
	std::map<unsigned short int, TILE> used;
	for (int i = 0; i < grid->getHeight()*grid->getWidth(); i++) {
		used[tiles[i].TILE_HASH] = tileMap->getTile(tiles[i].TILE_HASH);
	}
	for (std::map<unsigned short int, TILE>::iterator it = used.begin(); it != used.end(); it++) {
		outfile << "%" << it->first << std::endl;
		outfile << it->second.path << std::endl;
		outfile << it->second.x << std::endl;
		outfile << it->second.y << std::endl;
		outfile << it->second.name << std::endl;
	}
	outfile << '}' << std::endl;
	outfile << std::endl;
	outfile << "$GRID" << std::endl;
	outfile << '{' << std::endl;
	
	for (int y = 0; y < grid->getHeight(); y++) {
		for (int x = 0; x < grid->getWidth(); x++) {
			outfile << tiles[x + (y * grid->getWidth())].TILE_HASH << " ";
		}
		outfile << std::endl;
	}
	outfile << '}' << std::endl;
	currentFile = savePath;
	outfile.close();
}


bool FileHelper::saveAs()
{
	std::string savePath = getSaveFile("Where to should this map be saved?");
	if (savePath.length() == 0)
		return false;
	std::cout << "Saving file name: " << savePath << std::endl;
	saveData(savePath);
	return true;
}

bool FileHelper::save() {
	if (currentFile.compare("") == 0)
		return saveAs();
	else {
		saveData(currentFile);
		return true;
	}
}

bool FileHelper::importSpriteSheet(std::string path)
{
	std::string fileName;
	if (path.compare("") == 0)
		fileName = getFileName("Select the text file with spritesheet data");
	else
		fileName = path;
	if (fileName.length() == 0)
		return false;
	std::string file = "";
	for (int i = 1; i <= fileName.size(); i++) {
		if (fileName.at(fileName.size() - i) != '\\' && fileName.at(fileName.size() - i) != '/') {
			file = fileName.at(fileName.size() - i) + file;
		}
		else
			break;
	}
	spritesheet_vect.push_back(file);
	SpriteSheet sheet(tileMap);
	return sheet.parse(fileName);
}

TEXT_BOX getTextField(int font_size, int text_length) {
	TEXT_BOX text_box = { sf::RectangleShape(sf::Vector2f(text_length * font_size * 1.0f, font_size + (font_size / 2)* 1.0f))
		, sf::Text() };
	text_box.text.setCharacterSize(font_size);
	text_box.text.setFillColor(sf::Color::Black);

	text_box.box.setFillColor(sf::Color(219, 208, 171));
	text_box.box.setOutlineThickness(3);

	return text_box;
}

bool FileHelper::querySave() 
{
	sf::RenderWindow window(sf::VideoMode(640, 200), "Would you like to save?", sf::Style::Close | sf::Style::Titlebar);
	sf::Font font;

	sf::RectangleShape windowBackground(sf::Vector2f(window.getSize()));
	windowBackground.setFillColor(sf::Color(255, 242, 226));
	
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

		window.draw(windowBackground);

		for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++) {
			if (i == currentFocus)
				buttons[i].box.setOutlineColor(sf::Color(255, 0, 0));
			else
				buttons[i].box.setOutlineColor(sf::Color(0, 0, 0));

			buttons[i].box.setPosition(25 + (i*(buttons[i].box.getSize().x + 25)), 100);

			buttons[i].text.setPosition(30 + (i*(buttons[i].box.getSize().x + 25)), 100);

			window.draw(buttons[i].box);
			window.draw(buttons[i].text);
		}

		window.display();
		
	}

	return false;
}

void FileHelper::queryNewGrid()
{
	sf::RenderWindow window(sf::VideoMode(640, 200), "Create a new map.", sf::Style::Close | sf::Style::Titlebar);
	sf::Font font;

	sf::RectangleShape windowBackground(sf::Vector2f(window.getSize()));
	windowBackground.setFillColor(sf::Color(255, 242, 226));

	sf::Text descriptor[3];
	descriptor[0].setString("Tile Size:");
	descriptor[1].setString("Grid Width:");
	descriptor[2].setString("Grid Height:");

	if (!font.loadFromFile("../Resources/arial.ttf"))
		std::cout << "Font failed to load" << std::endl;
	TEXT_BOX buttons[3] = { getTextField(18, 10),  getTextField(18, 10), getTextField(18, 10) };
	for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++) {
		buttons[i].text.setFont(font);

		descriptor[i].setFillColor(sf::Color::Black);
		descriptor[i].setFont(font);
		descriptor[i].setCharacterSize(24);

		descriptor[i].setPosition(30 + (i*(buttons[i].box.getSize().x + 25)), 60);
	}

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
					spritesheet_vect.clear();
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
		window.draw(windowBackground);

		for (int i = 0; i < sizeof(buttons) / sizeof(TEXT_BOX); i++) {
			if (i == currentFocus)
				buttons[i].box.setOutlineColor(sf::Color(255, 0, 0));
			else
				buttons[i].box.setOutlineColor(sf::Color(0, 0, 0));

			buttons[i].box.setPosition(25 + (i*(buttons[i].box.getSize().x + 25)), 100);

			buttons[i].text.setPosition(30 + (i*(buttons[i].box.getSize().x + 25)), 100);

			window.draw(descriptor[i]);
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
	case LOAD:
		if (querySave())
			loadMap();
		break;
	case IMPORT:
		importSpriteSheet("");
		break;
	case EXIT:
		return querySave();
	}
	
	return false;
}


