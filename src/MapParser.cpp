//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#include "MapParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Board.h"
MapParser::MapParser(std::string path) {
    this->path = path;
}

MapParser::~MapParser() {
}

std::string MapParser::load() {
    std::ifstream file(this->path);
    std::stringstream buffer;



    buffer << file.rdbuf();

    return buffer.str();
}

Board MapParser::parse() {
    std::string content = this->load();
    int width;
    int height;
    std::vector<std::string> parts = this->split(content, 'P');
    std::vector<std::string> sizes = this->split(parts[0], 'x');
    width = std::stoi(sizes[0]);
    height = std::stoi(sizes[1]);
    Board board = Board(width, height);
    std::vector<std::string> cells = this->split(parts[1], ',');
    if (cells.size() % 2 != 0) {
        std::cout << "Invalid map" << std::endl;
        return board;
    }
    for (int i = 0; i < cells.size(); i += 2) {
        int x = std::stoi(cells[i]);
        int y = std::stoi(cells[i + 1]);
        board.setCell(x, y, true);
    }
    return board;
}

std::vector<std::string> MapParser::split(std::string s, char delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + 1);
    }
    tokens.push_back(s);
    return tokens;
}