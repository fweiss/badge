#include "Gravity.h"

#include <math.h>

Gravity::Gravity(Display &display) : Animation(display, 100) {
    this->motionData = { 0.0, 0.0, 0.0 };
    this->board = std::vector<std::vector<Cell*>>(8, std::vector<Cell*>(8, NULL));
    this->initBoard();
}

Gravity::~Gravity() {
}

int b(float x) {
    if (x > 7) x = 7;
    if (x < 0) x = 0;
    return x;
}

void Gravity::initBoard() {
    ZColor color = { .flat = 0xa04040ff };
    Cell* cell = new Cell(color);
    this->board[2][3] = cell;
}

void Gravity::drawFrame() {
    // updateSimpleFrame();
    drawBoard();
    display.update();
}

void Gravity::drawBoard() { // need updateBoard()
    display.clear();
    const int rows = 8;
    const int cols = 8;
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            Cell* cell = this->board[r][c]; // [r, c]?]
            if (cell) {
                this->paintPixel(r, c, cell->color);
            }
        }
    }
}

void Gravity::paintPixel(uint16_t row, uint16_t col, ZColor& color) {
    int offset = row * 8 + col;
    display.setPixel(offset, color.comp.r, color.comp.g, color.comp.b);   
}


void Gravity::updateSimpleFrame() {
    display.clear();

    // debug verify addressing
    // int p = this->x + (8 * this->y);
    // display.setPixel(p, 10, 10, 160);
    // this->x = (this->x + 1) % 8;
    // if (this->x == 0) {
    //     this->y = (this->y + 1) % 8;
    // }

    const float ax = this->motionData.ax;
    const float ay = this->motionData.ay;

    // float r = sqrt(ax * ax + ay * ay);
    // float angle = atan2(this->motionData.ay, this->motionData.ax);
    // float r *= 4.2; // empirical to reach corners 
    // float dx = r * cos(angle);
    // float dy = r * - sin(angle); // top-down

    float r = 4.7;
    float dx = r * ax;
    float dy = r * - ay;

    int ox = b(3.5 + dx);
    int oy = b(3.5 + dy);
    printf("offsets %d, %d\n", ox, oy);

    int offset = ox + 8 * oy;
    if (offset > 63) {
        offset = 63;
    }
    display.setPixel(offset, 160, 160, 10);
}

void Gravity::setMotion(MotionData motionData) {
    this->motionData = motionData;
}
