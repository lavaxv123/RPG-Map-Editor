#include <Windows.h>
#include "FileHelper.h"
#include "SpriteSheet.h"
#include <iostream>
#include <fstream>


FileHelper::FileHelper(Grid * grid, TileMap * tileMap)
{
	FileHelper::grid = grid;
	FileHelper::tileMap = tileMap;

	query = new QueryWindow(grid);
}

FileHelper::~FileHelper() {
	delete query;
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
		std::cout << filePath.substr(filePath.length() - 4, filePath.length()).compare(".txt") << std::endl;
		return filePath;
	}
	else {
		filePath += ".TXT";
		return filePath;
	}
}

bool FileHelper::loadMap()
{
	std::string fileName = getFileName("Select the text file with spritesheet data");
	if (fileName.length() == 0)
		return false;
	SpriteSheet sheet(tileMap);
	sheet.parse(fileName);
	return false;
}

bool FileHelper::saveMap()
{
	std::string savePath = getSaveFile("Where to should this map be saved?");
	if (savePath.length() == 0)
		return false;
	std::cout << "Saving file name: " << savePath << std::endl;
	std::ofstream outfile(savePath);
	outfile.clear();
	outfile << "my text here!" << std::endl;

	outfile.close();
	return false;
}

bool FileHelper::importSpriteSheet()
{
	std::string fileName = getFileName("Select the text file with spritesheet data");
	if (fileName.length() == 0)
		return false;
	SpriteSheet sheet(tileMap);
	sheet.parse(fileName);
	return false;
}


void FileHelper::initGrid() 
{
	
}
