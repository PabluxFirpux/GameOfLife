#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "Board.h"
#include "MapParser.h"

int WIDTH = 1800;
int HEIGHT = 900;
const int BOARD_SIZE = 600;
int CELL_SIZE = 10;
int XOFFSET = 0;
int YOFFSET = 0;
bool grid = false;
MapParser parser = MapParser("");
Board board = Board(BOARD_SIZE, BOARD_SIZE, true);

void display();

void reshape(int w, int h);

void drawCell(float x, float y);

void drawCellWithoutBorder(float x, float y);

void drawCellWithBorder(float x, float y);

void pressKey(unsigned char key, int x, int y);

void drawBoard();

void init() {
    glClearColor(0, 0, 0, 255);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        parser = MapParser(argv[1]);
        board = parser.parse();
        board.pause();
    } else {
        board = Board(BOARD_SIZE, BOARD_SIZE, true);
        board.pause();
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Game of Life");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(pressKey);
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
    WIDTH = w;
    HEIGHT = h;
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
    drawCellWithoutBorder(x, y);
}

void drawCellWithoutBorder(float x, float y) {
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x + CELL_SIZE, y);
    glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2f(x, y + CELL_SIZE);
}

void drawCellWithBorder(float x, float y) {
    glColor3f(1, 1, 1);
    glVertex2f(x, y);
    glVertex2f(x + CELL_SIZE, y);
    glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2f(x, y + CELL_SIZE);

    glColor3f(0, 0, 0);
    float borderThickness = CELL_SIZE / 10;
    float newCellSize = CELL_SIZE - 2 * borderThickness;
    float newX = x + borderThickness;
    float newY = y + borderThickness;
    glVertex2f(newX, newY);
    glVertex2f(newX + newCellSize, newY);
    glVertex2f(newX + newCellSize, newY + newCellSize);
    glVertex2f(newX, newY + newCellSize);
}

void drawBoard() {
    for (int i = 0; i < WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; j++) {
            if (board.isAlive(i + XOFFSET, j + YOFFSET)) drawCell(i * CELL_SIZE, j * CELL_SIZE);
            else if (grid) drawCellWithBorder(i * CELL_SIZE, j * CELL_SIZE);
        }
    }
}

void pressKey(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            if (YOFFSET < BOARD_SIZE - (HEIGHT / CELL_SIZE))
                YOFFSET++;
            break;
        case 's':
            if (YOFFSET > 0)
                YOFFSET--;
            break;
        case 'a':
            if (XOFFSET > 0)
                XOFFSET--;
            break;
        case 'd':
            if (XOFFSET < BOARD_SIZE - (WIDTH / CELL_SIZE))
                XOFFSET++;
            break;
        case 'q':
            if (BOARD_SIZE > WIDTH / CELL_SIZE)
                CELL_SIZE--;
            break;
        case 'e':
            CELL_SIZE++;
            break;
        case 'r':
            board = parser.parse();
            board.pause();
            break;
        case 'g':
            grid = !grid;
            break;
        case 't':
            board = Board(BOARD_SIZE, BOARD_SIZE, true);
            board.pause();
            break;
        case ' ':
            board.update();
            break;
        case 'x':
            exit(0);
            break;
        case 'p':
            board.pause();
            break;
        case 'n':
            board.pause();
            board.update();
            board.pause();
            break;
    }
}
