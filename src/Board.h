//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

#include "Cell.h"
#include <vector>
#include <string>
class Board {
public:
    Board(int width, int height);
    ~Board();
    void update();
    std::vector<std::vector<Cell>> getView();
    bool isAlive(int x, int y);
    void setCell(int x, int y, bool alive);
    void setCell(int x, int y, Cell cell);
    Cell getCell(int x, int y);
    int getWidth();
    int getHeight();
    void pause();
private:
    bool paused;
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;
    void updateCell(int x, int y);
    int countAliveNeighbours(int x, int y);
};


#endif //GAMEOFLIFE_BOARD_H
