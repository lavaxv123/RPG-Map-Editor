#include "SpriteSheet.h"
#include <iostream>
#include <fstream>
#include <vector>
SpriteSheet::SpriteSheet(TileMap* tileMap)
{
	SpriteSheet::tileMap = tileMap;
}


SpriteSheet::~SpriteSheet()
{
}

std::vector<std::string> split(std::string str, char splitAt) {
	std::vector<std::string> data;
	std::string curr_str;
	for (int i = 0; i < str.length(); i++) {
		if(str[i] != splitAt){
			curr_str += str[i];
		}
		else if (curr_str != "") {
			data.push_back(curr_str);
			curr_str = "";
		}

	}
	if (curr_str != "") {
		data.push_back(curr_str);
	}
	for (int i = 0; i < data.size(); i++) {
		std::cout << i << " : " <<data[i] << std::endl;
	}
	return data;
}

bool SpriteSheet::load(std::string spritesheet_path, std::string detail_path) {
	std::string curr_line;
	std::ifstream in;
	sf::Image spritesheet;
	spritesheet.loadFromFile(spritesheet_path);
	in.open(detail_path);
	
	while (std::getline(in,curr_line) ) {
		std::cout << curr_line << std::endl;
		std::vector<std::string> data = split(curr_line, ' ');
		std::cout << data.size() << std::endl;
		if (data.size() != 4) {
			return false;
		}
		sf::Texture texture;
		texture.loadFromImage(spritesheet, sf::IntRect(std::stoi(data[0]) * std::stoi(data[1]), 
													   std::stoi(data[0]) * std::stoi(data[1]),
													  (std::stoi(data[0]) * std::stoi(data[1])) + std::stoi(data[0]),
													  (std::stoi(data[0]) * std::stoi(data[1])) + std::stoi(data[0])));
		tileMap->add(data[3],texture,std::stoi(data[0]));
	}
	in.close();
	return true;
}