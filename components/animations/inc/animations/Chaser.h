#pragma once

// folowing to fix Arduino.h when using stdlib
#undef max
#undef min

#include <stdint.h>
#include <deque>

class Chaser {
public:
    Chaser(uint16_t size);
    Chaser(uint16_t size, uint16_t step);
    virtual ~Chaser() {};

    void roll();
    virtual uint32_t nextColor() = 0;
    void setReverse(bool reverse);
    uint32_t get(uint16_t index);
    void preroll(uint16_t amount);
protected:
    std::deque<uint32_t> colors;
    const uint16_t step;
private:
    bool reverse;
};
