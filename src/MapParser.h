//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#ifndef GAMEOFLIFE_MAPPARSER_H
#define GAMEOFLIFE_MAPPARSER_H

#include "Board.h"
#include <string>
class MapParser {
public:
    MapParser(std::string path);
    ~MapParser();
    Board parse();
    std::string load();
    void setPath(std::string path);
    std::string getPath();
private:
    std::string path;
    std::vector<std::string> split(std::string str, char delimiter);
};


#endif //GAMEOFLIFE_MAPPARSER_H
