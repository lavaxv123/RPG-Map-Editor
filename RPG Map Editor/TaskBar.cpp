#include "TaskBar.h"
#include "TileMap.h"
#include <iostream>

#define LEFT_PANEL_SIZE 321.f
#define TASK_BAR_SIZE 30.f
#define FILE_DROPDOWN_NUMBER 6
#define TOOLS_DROPDOWN_NUMBER 7
#define OFFSET 28
#define TICK_DELAY 75

TaskBar::TaskBar(sf::RenderWindow* window, FileHelper* fileHelper)
{
	file = new sf::RectangleShape(sf::Vector2f(60.f, 22.f));
	fileNew = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	saveMap = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	openMap = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	importSpritesheet = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	exitProgram = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	saveAs = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));

	tools = new sf::RectangleShape(sf::Vector2f(60.f, 22.f));
	toolsPen = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	toolsFilledRect = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));
	toolsOuterRect = new sf::RectangleShape(sf::Vector2f(150.f, 25.f));

	arial.loadFromFile("../Resources/arial.ttf");
	TaskBar::window = window;
	TaskBar::fileHelper = fileHelper;


	isFileVisible = false;
	isToolsVisible = false;
}


TaskBar::~TaskBar()
{
	delete file;
	delete saveMap;
	delete openMap;
	delete importSpritesheet;
	delete exitProgram;
	delete saveAs;

	delete tools;
	delete toolsPen;
	delete toolsFilledRect;
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

	//Renders the drop down menu for Tools

	sf::RectangleShape toolsDropDown(sf::Vector2f(150.f, (float)(25 * TOOLS_DROPDOWN_NUMBER)));
	toolsDropDown.setFillColor(sf::Color(255, 242, 226));
	toolsDropDown.setOutlineThickness(1);
	toolsDropDown.setOutlineColor(sf::Color(119, 119, 119));
	toolsDropDown.setPosition(385, 28);

	if (isFileVisible == true) {
		window->draw(fileDropDown);
	}
	if (isToolsVisible) {
		window->draw(toolsDropDown);
	}
	if (fileDropDown.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1 && file->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1) {
		isFileVisible = false;
	}
	if (toolsDropDown.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1 && tools->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) != 1) {
		isToolsVisible = false;
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
	
	//Render tools button
	tools->setFillColor(sf::Color(219, 208, 171));
	tools->setOutlineThickness(1);
	tools->setOutlineColor(sf::Color(110, 110, 110));
	tools->setPosition(384, 4);

	sf::Text toolsTXT("Tools", arial, 16);
	toolsTXT.setPosition(386, 4);
	toolsTXT.setFillColor(sf::Color(0, 0, 0));

	window->draw(*tools);
	window->draw(toolsTXT);

	//MAP
	//Create the hitbox for creating a new map
	fileNew->setPosition(322, OFFSET);

	//Render the map text
	sf::Text newTXT("New", arial, 16);
	newTXT.setPosition(323, OFFSET);
	newTXT.setFillColor(sf::Color(0, 0, 0));

	//SAVE AS
	//Create the hitbox for saving the map
	saveAs->setPosition(322, OFFSET + 25);

	//Render the save as text
	sf::Text saveAsTXT("Save As", arial, 16);
	saveAsTXT.setPosition(323, OFFSET + 25);
	saveAsTXT.setFillColor(sf::Color(0, 0, 0));
	
	//SAVE
	//Create the hitbox for saving the map
	saveMap->setPosition(322, OFFSET + 25*2);

	//Render the save text
	sf::Text saveTXT("Save", arial, 16);
	saveTXT.setPosition(323, OFFSET + 25*2);
	saveTXT.setFillColor(sf::Color(0, 0, 0));

	//OPEN 
	//Create the hitbox for opening a saved map
	openMap->setPosition(322, OFFSET + 25*3);

	//Render the open text
	sf::Text openTXT("Open", arial, 16);
	openTXT.setPosition(323, OFFSET + 25*3);
	openTXT.setFillColor(sf::Color(0, 0, 0));
	
	//IMPORT SPRITESHEET
	//Create the hitbox for importing a sprite sheet into the editor
	importSpritesheet->setPosition(322, OFFSET + 25*4);

	//Render the Spritesheet text
	sf::Text importTXT("Import Spritesheet", arial, 16);
	importTXT.setPosition(323, OFFSET + 25*4);
	importTXT.setFillColor(sf::Color(0, 0, 0));
	
	//EXIT
	//Create the hitbox for Exiting the program
	exitProgram->setPosition(322, OFFSET + 25*5);

	//Render the exit text
	sf::Text exitTXT("Exit", arial, 16);
	exitTXT.setPosition(323, OFFSET + 25*5);
	exitTXT.setFillColor(sf::Color(0, 0, 0));

	/******************************************************/

	//TOOLS
	//Creating the button for the Pen tool
	toolsPen->setPosition(385, OFFSET);

	//Render the Pen text
	sf::Text penTXT("Pen", arial, 16);
	penTXT.setPosition(386, OFFSET);
	penTXT.setFillColor(sf::Color(0, 0, 0));

	//Creating the button for the Filled Rect tool
	toolsFilledRect->setPosition(385, OFFSET + 25);

	//Render the text
	sf::Text fRectTXT("Filled Rectangle", arial, 16);
	fRectTXT.setPosition(386, OFFSET + 25);
	fRectTXT.setFillColor(sf::Color(0, 0, 0));

	//Creating the button for the Outline Rect tool
	toolsOuterRect->setPosition(385, OFFSET + 50);

	//Render the text
	sf::Text oRectTXT("Rectangle Outline", arial, 16);
	oRectTXT.setPosition(386, OFFSET + 50);
	oRectTXT.setFillColor(sf::Color(0, 0, 0));


	if (isFileVisible == true) {
		window->draw(newTXT);
		window->draw(saveAsTXT);
		window->draw(saveTXT);
		window->draw(openTXT);
		window->draw(importTXT);
		window->draw(exitTXT);
	}
	else if (isToolsVisible) {
		window->draw(penTXT);
		window->draw(fRectTXT);
		window->draw(oRectTXT);
	}
}

void TaskBar::input()
{
	if (file->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
		isFileVisible = true;
	}
	else if (fileNew->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		fileHelper->openQuery(NEW);
	}
	else if (saveAs->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		fileHelper->openQuery(SAVE_AS);
	}
	else if (openMap->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		fileHelper->openQuery(LOAD);
	}
	else if (importSpritesheet->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		fileHelper->openQuery(IMPORT);
	}
	else if (exitProgram->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) {
		if (fileHelper->openQuery(EXIT))
			window->close();
	}
	else if ((saveMap->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isFileVisible) 
		|| ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
		fileHelper->openQuery(SAVE);
		isFileVisible = false;
	}
	else if (tools->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
		isToolsVisible = true;
	}
	else if (toolsPen->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isToolsVisible) {
		fileHelper->mouseModeToGrid(PEN);
		std::cout.flush();
		Sleep(TICK_DELAY);
	}
	else if (toolsFilledRect->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isToolsVisible) {
		fileHelper->mouseModeToGrid(FILLED_RECT);
		std::cout.flush();
		Sleep(TICK_DELAY);
	}
	else if (toolsOuterRect->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && isToolsVisible) {
		fileHelper->mouseModeToGrid(OUTER_RECT);
		std::cout.flush();
		Sleep(TICK_DELAY);
	}
}

bool TaskBar::isDropDownOpen()
{
	if (isFileVisible == true)
		return true;
	else if (isToolsVisible == true)
		return true;
	else
		return false;
}