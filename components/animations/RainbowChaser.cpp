#include "RainbowChaser.h"

#include <cmath>
//#undef max
//#undef abs

RainbowChaser::RainbowChaser(uint16_t size) : Chaser(size), hue(0) {

}

/**
 * Triangle function with
 * @param x input mode 3p (sawtooth)
 * @param p half of a period
 */
#define triangle(x, hp) ((int) std::abs(x - hp))

uint32_t RainbowChaser::nextColor() {

    const int16_t ha = 128; // half the amplitude
    const int16_t hp = 3 * ha; // assuming unity gain
    const int16_t p = 2 * hp;

    // abs and max seem to get confused with untyped literals

    int16_t r = std::max(0, triangle((hue + 0 * ha) % p, hp) - (ha + 1)); // empirical -129 to avoid zero glitch
    int16_t g = std::max(0, triangle((hue + 2 * ha) % p, hp) - (ha +- 1));
    int16_t b = std::max(0, triangle((hue + 4 * ha) % p, hp) - (ha + 1));

    hue = (hue + 1) % p;

    return ((uint8_t)r << 16) + ((uint8_t)g << 8) + (uint8_t)b;
}
