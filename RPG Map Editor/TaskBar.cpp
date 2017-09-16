#include "TaskBar.h"
#include "TileMap.h"
#include <iostream>

#define LEFT_PANEL_SIZE 321.f
#define TASK_BAR_SIZE 30.f
#define FILE_DROPDOWN_NUMBER 4

TaskBar::TaskBar(sf::RenderWindow* window, FileHelper* fileHelper)
{
	file = new sf::RectangleShape(sf::Vector2f(60.f, 22.f));
	fileNew = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	saveMap = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	openMap = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	importSpritesheet = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));

	arial.loadFromFile("../Resources/arial.ttf");
	TaskBar::window = window;
	TaskBar::fileHelper = fileHelper;

	isFileVisible = false;
}


TaskBar::~TaskBar()
{
	delete file;
	delete saveMap;
	delete openMap;
	delete importSpritesheet;
}

void TaskBar::render()
{

	//Sets view for rendering task bar
	sf::View taskView(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	taskView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	window->setView(taskView);



	//Renders the bar at the top of the screen

	sf::RectangleShape taskBar(sf::Vector2f((float)(window->getSize().x - 321), 24));
	taskBar.setFillColor(sf::Color(255, 242, 226));
	taskBar.setOutlineThickness(3);
	taskBar.setOutlineColor(sf::Color(119, 119, 119));
	taskBar.setPosition(321, 3);
	window->draw(taskBar);

	//Renders the drop down menu for File
	
	sf::RectangleShape fileDropDown(sf::Vector2f(150.f, (float)(25*FILE_DROPDOWN_NUMBER)));
	fileDropDown.setFillColor(sf::Color(255, 242, 226));
	fileDropDown.setOutlineThickness(1);
	fileDropDown.setOutlineColor(sf::Color(119, 119, 119));
	fileDropDown.setPosition(322, 28);




	if (isFileVisible == true) {
		window->draw(fileDropDown);
	}
	if (fileDropDown.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1 && file->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1) {
		isFileVisible = false;
	}

	renderButtons();
}

void TaskBar::renderButtons()
{

	
	//Render file button
	file->setFillColor(sf::Color(219, 208, 171));
	file->setOutlineThickness(1);
	file->setOutlineColor(sf::Color(110, 110, 110));
	file->setPosition(321, 4);

	sf::Text fileTXT("File", arial, 16);
	fileTXT.setPosition(323, 4);
	fileTXT.setFillColor(sf::Color(0, 0, 0));

	window->draw(*file);
	window->draw(fileTXT);
	
	//MAP
	//Create the hitbox for creating a new map
	fileNew->setPosition(322, 28);

	//Render the save text
	sf::Text newTXT("New", arial, 16);
	newTXT.setPosition(323, 30);
	newTXT.setFillColor(sf::Color(0, 0, 0));

	//SAVE
	//Create the hitbox for saving the map
	saveMap->setPosition(322, 53);

	//Render the save text
	sf::Text saveTXT("Save", arial, 16);
	saveTXT.setPosition(323, 55);
	saveTXT.setFillColor(sf::Color(0, 0, 0));

	//OPEN 
	//Create the hitbox for opening a saved map
	openMap->setPosition(322, 78);

	//Render the save text
	sf::Text openTXT("Open", arial, 16);
	openTXT.setPosition(323, 80);
	openTXT.setFillColor(sf::Color(0, 0, 0));
	
	//IMPORT SPRITESHEET
	//Create the hitbox for importing a sprite sheet into the editor
	importSpritesheet->setPosition(322, 103);

	//Render the save text
	sf::Text importTXT("Import Spritesheet", arial, 16);
	importTXT.setPosition(323, 105);
	importTXT.setFillColor(sf::Color(0, 0, 0));
	
	if (isFileVisible == true) {
		window->draw(newTXT);
		window->draw(saveTXT);
		window->draw(openTXT);
		window->draw(importTXT);
	}
}

void TaskBar::input()
{
	if (file->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
		isFileVisible = true;
	}
	if (fileNew->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {

	}
	else if (saveMap->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		std::cout << "noob" << std::endl;
		fileHelper->saveMap();
	}
	else if (openMap->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		std::cout << "noob" << std::endl;
		fileHelper->loadMap();
	}
	else if (importSpritesheet->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		std::cout << "noob" << std::endl;
		fileHelper->importSpriteSheet();
	}
}

bool TaskBar::isDropDownOpen()
{
	if (isFileVisible == true)
		return true;
	else
		return false;
}