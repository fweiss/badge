#pragma once

#include "Animation.h"
#include "motion/Motion.hpp"

#include <vector>

// todo rename and move to Frame.h
union ZColor {
    uint32_t flat;
    struct {
        // uint8_t l, b, g, r; // LE
        // uint8_t g, r, b, l;
        uint8_t r : 8;
        uint8_t g : 8;
        uint8_t b : 8;
        uint8_t l : 8; 
    } comp;

    ZColor() { flat = 0; };
    ZColor(uint32_t flat) { this->flat = flat; };
    ZColor(uint8_t r, uint8_t g, uint8_t b) { 
        // comp = { .g{g}, .r{r}, .b{b}, .l{0} };
        comp.r = r;
        comp.g = g;
        comp.b = b;
        comp.l = 255;
    };
};

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
    Gravity();
    virtual ~Gravity();

    virtual void drawFrame(Frame &frame) override;

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
