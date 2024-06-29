#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>

#include "Chaser.h"

class Frame {
public:
    // no constructor, this is an interface

    // will probably also want non-liear accessors and Color objects
    virtual void clear() = 0;
    virtual void setPixel(uint16_t p, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void setPixel(uint16_t p, uint32_t color) = 0;

    // maybe this is only needed for the matrix
    // virtual uint8_t * data() = 0;
    // virtual size_t length() = 0;

    // not needed for now
    // virtual size_t width() = 0;
    // virtual size_t height() = 0;

    // helpers
    void drawPath(std::vector<uint16_t> path, Chaser *chaser);
    void draw(std::vector<uint32_t> frame);
    void drawPath(std::vector<uint16_t> path, uint32_t color);
};
