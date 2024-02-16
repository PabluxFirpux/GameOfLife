//
// Created by Pablo Firpo Molina on 12/02/2024.
//

#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H


class Cell {
public:
    Cell();
    ~Cell();
    void setAlive(bool alive);
    bool isAlive();
    void setNextState(bool nextState);
    bool getNextState();
    void updateState();
private:
    bool alive;
    bool nextState;
};


#endif //GAMEOFLIFE_CELL_H
