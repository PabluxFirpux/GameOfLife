#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "Board.h"

const int WIDTH = 1800;
const int HEIGHT = 900;
const int CELL_SIZE = 10;
Board board(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);

void display();
void reshape(int w, int h);
void drawCell(float x, float y);
void drawBoard();

void init() {
    glClearColor(0, 0, 0,255);
}

int main(int argc, char** argv) {
    std::cout << "Initializing life" << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Game of Life");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();

    return 0;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    board.update();
    glBegin(GL_QUADS);

    drawBoard();

    glEnd();

    glFlush();
}

void drawCell(float x, float y) {
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x + CELL_SIZE, y);
    glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2f(x, y + CELL_SIZE);

}

void drawBoard() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            if (board.getCell(i, j).isAlive()) {
                drawCell(i * CELL_SIZE, j * CELL_SIZE);
            }
        }
    }
}
