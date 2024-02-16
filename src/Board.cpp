//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#include "Board.h"
#include "Cell.h"
#include <vector>
#include <cstdlib>

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
    for (int i = 0; i < width; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < height; j++) {
            int random = rand() % 10 +1;
            row.push_back(Cell(i, j, random > 5));
        }
        this->cells.push_back(row);
    }
}

Board::~Board() {
}

void Board::update() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->updateCell(i, j);
        }
    }
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->cells[i][j].updateState();
        }
    }
}

void Board::updateCell(int x, int y) {
    int aliveNeighbours = this->countAliveNeighbours(x, y);
    if (this->cells[x][y].isAlive()) {
        if (aliveNeighbours < 2 || aliveNeighbours > 3) {
            this->cells[x][y].setNextState(false);
        }
    } else {
        if (aliveNeighbours == 3) {
            this->cells[x][y].setNextState(true);
        }
    }
}

int Board::countAliveNeighbours(int x, int y) {
    int aliveNeighbours = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int neighbourX = x + i;
            int neighbourY = y + j;
            if (neighbourX >= 0 && neighbourX < this->width && neighbourY >= 0 && neighbourY < this->height) {
                if (this->cells[neighbourX][neighbourY].isAlive()) {
                    aliveNeighbours++;
                }
            }
        }
    }
    return aliveNeighbours;
}

std::vector<std::vector<Cell>> Board::getView() {
    return this->cells;
}

Cell Board::getCell(int x, int y) {
    return this->cells[x][y];
}

bool Board::isAlive(int x, int y) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return false;
    }
    return this->cells[x][y].isAlive();
}