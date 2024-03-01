//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#include "Board.h"
#include "Cell.h"
#include <vector>
#include <cstdlib>
#include <iostream>

Board::Board(int width, int height, bool randomBoard) {
    this->width = width;
    this->height = height;
    this->paused = false;
    for (int i = 0; i < width; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < height; j++) {
            int random = rand() % 10 +1;
            Cell cell = Cell(i, j, randomBoard && random > 5);
            row.push_back(cell);
        }
        this->cells.push_back(row);
        for (auto cell : cells[i]) {
            if (cell.isAlive()) {
                Cell* cellPointer = &cell;
                this->aliveCells.push_back(cellPointer);
            }
        }
    }
}

Board::~Board() {
}

void Board::update() {
    if (this->paused) {
        return;
    }

    std::vector<Cell*> cellsAlive;
    cellsAlive.reserve(this->aliveCells.size());
    for (auto aliveCell : this->aliveCells) {
        cellsAlive.push_back(aliveCell);
    }
    this->aliveCells.clear();

    for (auto cell : cellsAlive) {
        Cell cellCopy = *cell;
        this->updateCellAndNeighbours(cell->getX(), cell->getY());
    }

    for (auto cell : this->cellsToUpdate) {
        this->changeState(cell->getX(), cell->getY());
    }
    this->cellsToUpdate.clear();

}

void Board::updateCell(int x, int y) {
    int aliveNeighbours = this->countAliveNeighbours(x, y);
    bool alive = this->cells[x][y].isAlive();
    if (alive) {
        if (aliveNeighbours < 2 || aliveNeighbours > 3) {
            this->cells[x][y].setNextState(false);
        } else {
            this->cells[x][y].setNextState(true);
            this->aliveCells.push_back(&this->cells[x][y]);
        }
    } else {
        if (aliveNeighbours == 3) {
            this->cells[x][y].setNextState(true);
            this->aliveCells.push_back(&this->cells[x][y]);

        } else {
            this->cells[x][y].setNextState(false);

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

void Board::setCell(int x, int y, bool alive) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return;
    }
    if (alive) {
        Cell* cellPointer = &this->cells[x][y];
        cellPointer->setAlive(true);
        this->aliveCells.push_back(cellPointer);
    }
}

bool Board::isAlive(int x, int y) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return false;
    }
    return this->cells[x][y].isAlive();
}

void Board::pause() {
    this->paused = !this->paused;
}


void Board::updateCellAndNeighbours(int x, int y) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int neighbourX = x + i;
            int neighbourY = y + j;

            if (neighbourX >= 0 && neighbourX < this->width && neighbourY >= 0 && neighbourY < this->height) {

                if(!this->cells[neighbourX][neighbourY].isChecked()) {
                    this->updateCell(neighbourX, neighbourY);
                    this->cellsToUpdate.push_back(&this->cells[neighbourX][neighbourY]);

                }
            }
        }
    }
}

void Board::changeState(int x, int y) {
    this->cells[x][y].updateState();
}
