//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H


class Cell {
public:
    Cell(int x, int y, bool alive = false);
    ~Cell();
    void setAlive(bool alive);
    bool isAlive();
    bool isChecked();
    void setNextState(bool nextState);
    bool getNextState();
    void updateState();
    int getX();
    int getY();
private:
    bool checked;
    bool alive;
    bool nextState;
    int x;
    int y;
};


#endif //GAMEOFLIFE_CELL_H
