#include <Windows.h>
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
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();
	//Might not work
	ofns.lpstrFilter = "PNG Files (*.png), *.png";
	GetOpenFileName(&ofns);
	return buffer;
}

bool FileHelper::loadMap()
{
	std::string fileName = getFileName("Load the png file");
	return false;
}

bool FileHelper::saveMap()
{
	return false;
}

bool FileHelper::importSpriteSheet()
{
	return false;
}
