//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#include "Cell.h"
Cell::Cell(int x, int y, bool alive) {
    this->alive = alive;
    this->x = x;
    this->y = y;
    this->checked = false;
}

bool Cell::isAlive() {
    return this->alive;
}

void Cell::setAlive(bool alive) {
    this->alive = alive;
}

void Cell::setNextState(bool nextState) {
    this->nextState = nextState;
    this->checked = true;
}

bool Cell::getNextState() {
    return this->nextState;
}

bool Cell::isChecked() {
    return this->checked;
}

int Cell::getX() {
    return this->x;
}

int Cell::getY() {
    return this->y;
}

void Cell::updateState() {
    this->alive = this->nextState;
    this->checked = false;
}

Cell::~Cell() {
}