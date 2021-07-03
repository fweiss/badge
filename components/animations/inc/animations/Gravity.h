#pragma once

#include "Animation.h"
#include "Display.h"
#include "motion/Motion.hpp"

#include <vector>

typedef union {
    uint32_t flat;
    struct {
        uint8_t r, g, b, l;
    } comp;
} ZColor;

class Cell {
public:
    Cell(ZColor color) { this->color = color; }
    ZColor color;
};

class Gravity : public Animation {
public:
    Gravity(Display &display);
    virtual ~Gravity();

    void drawFrame() override;

    void setMotion(MotionData motionData);
private:
    MotionData motionData;
    void updateSimpleFrame();
    uint8_t x,y;
    std::vector<std::vector<Cell*>> board;
    void initBoard();
    void drawBoard();
    void paintPixel(uint16_t r, uint16_t c, ZColor& color);
};
