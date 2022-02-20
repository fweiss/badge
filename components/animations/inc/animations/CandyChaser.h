#pragma once

#include "Chaser.h"

class CandyChaser : public Chaser {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t dr;
    uint8_t dg;
    uint8_t db;
protected:
public:
    CandyChaser(uint8_t r, uint8_t g, uint8_t b);
    CandyChaser(uint16_t size);
    uint32_t nextColor() override;
    static uint32_t createRgbColor(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
};
