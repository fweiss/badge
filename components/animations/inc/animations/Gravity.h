#pragma once

#include "Animation.h"
#include "Display.h"
#include "motion/Motion.hpp"

#include <vector>

typedef union {
    uint32_t flat;
    struct {
        uint8_t l, b, g, r; // LE
    } comp;
} ZColor;

class Cell {
public:
    Cell(ZColor color) { this->color = color; }
    ZColor color;
};

typedef struct {
    int r;
    int c;
} CPoint;

class Gravity : public Animation {
public:
    Gravity(Display &display);
    virtual ~Gravity();

    void drawFrame() override;

    void setMotion(MotionData motionData);
private:
    MotionData motionData;
    std::vector<std::vector<Cell*>> board;
    std::vector<CPoint> allPoints;

    void updateSimpleFrame();
    uint8_t x,y;
    void initBoard();  // @deprecate
    void initBoardRandom();
    void drawBoard();
    void paintPixel(uint16_t r, uint16_t c, ZColor& color);
    void updateBoardMotion(MotionData motionData);
};
