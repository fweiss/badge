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

/** A cell, which has a color */
class Cell {
public:
    Cell(ZColor color) { this->color = color; }
    ZColor color;
};

/** A point as row and column */
typedef struct {
    int r;
    int c;
} CPoint;

/** Associate cost with a point */
typedef struct {
    CPoint point;
    float cost;
} TargetCost;

/** Associate the list of target costs with a source point */
typedef struct {
    CPoint point;
    std::vector<TargetCost> choices;
} SourceChoices;

class Gravity : public Animation {
public:
    Gravity(Display &display);
    virtual ~Gravity();

    void drawFrame() override;

    void setMotion(MotionData motionData);
private:
    MotionData motionData;
    std::vector<std::vector<Cell*>> board;
    /** A linear list of all the cells. */
    std::vector<CPoint> allPoints;
    /** Concave potential gradient */
    std::vector<std::vector<float>> concaveBias;

    void updateSimpleFrame();
    uint8_t x,y;
    void initBoardRandom();
    void drawBoard();
    void paintPixel(uint16_t r, uint16_t c, ZColor& color);
    void updateBoardMotion(MotionData motionData);
    void gentleDrop(SourceChoices &move);
};
