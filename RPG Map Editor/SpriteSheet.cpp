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

std::vector<std::string> getTileData(std::string str) {
	std::vector<std::string> data;
	std::string curr_str;
	std::cout << str << std::endl;
	bool found = false;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '"') {
			if (found) {
				found = false;
				data.push_back(curr_str);
				curr_str = "";
			}
			else {
				found = true;
			}
		}
		else if (found)
			curr_str += str[i];
		else {
			if (str[i] != ' ') {
				curr_str += str[i];
			}
			else if (curr_str != "") {
				data.push_back(curr_str);
				curr_str = "";
			}
		}
	}
	if (curr_str != "") {
		data.push_back(curr_str);
	}
	return data;
}

bool SpriteSheet::parse(std::string txt_file) {
	std::string curr_line;
	std::ifstream in(txt_file);
	if (!in.good()) {
		std::cout << "Could not find file" << std::endl;
		return false;
	}
	std::string path;
	sf::Image spritesheet;
	while (std::getline(in, curr_line)) {
		if (curr_line.length() == 0)
			continue;
		switch (curr_line[0]) {
		case '$': {
			std::string spritesheet_path;
			bool found = false;
			for (unsigned int i = 0; i < curr_line.length(); i++) {
				if (curr_line[i] == '"') {
					if (found) {
						if (!spritesheet.loadFromFile(spritesheet_path)) {
							std::cout << spritesheet_path <<" Could not load spritesheet."  <<std::endl;
							return false;
						}
						else {
							path = spritesheet_path;
							std::cout << spritesheet_path << " loaded." <<std::endl;
						}
						break;
					}
					else
						found = true;
				}
				else if (found) {
					spritesheet_path += curr_line[i];
				}
			}
		} break;
		case '{':
			while (curr_line[0] != '}') {
				std::getline(in, curr_line);
				if (curr_line.length() != 0 && curr_line[0] == '}')
					break;
				if (spritesheet.getSize().x != 0) {
					std::vector<std::string> data = getTileData(curr_line);
					if (data.size() == 4) {
						sf::Texture* texture = new sf::Texture();

						/**
						data[0] = size
						data[1] = x
						data[2] = y
						data[3] = name
						*/
						texture->loadFromImage(spritesheet, sf::IntRect(std::stoi(data[0]) * std::stoi(data[1]),
							std::stoi(data[0]) * std::stoi(data[2]),
							std::stoi(data[0]),
							std::stoi(data[0])));
						tileMap->add(data[3], texture, std::stoi(data[0]), std::stoi(data[1]),
							std::stoi(data[2]), path);
					}
				}
			} break;
		}
	}
	return true;
}

