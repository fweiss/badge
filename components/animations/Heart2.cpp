#include "Heart2.h"

Heart2::Heart2(Display &display) : BitmapAnimation(display, heart) {

}

#define red 0x640000
#define purple 0x640064

std::vector<std::vector<uint32_t>> Heart2::heart = {
    {
        0, red, red, 0, 0 , red, red, 0,
        red, red, purple, red, red, purple, red, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, 0, red, 0, 0, red, 0, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, red, red, 0, 0 , red, red, 0,
        red, red, red, red, red, red, red, red,
        red, red, red, red, red, red, red, red,
        red, red, red, red, red, red, red, red,
        red, red, red, red, red, red, red, red,
        0, red, red, red, red, red, red, 0,
        0, 0, red, red, red, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, 0, red, 0, 0, red, 0, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, red, red, 0, 0 , red, red, 0,
        red, red, purple, red, red, purple, red, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, 0, red, 0, 0, red, 0, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, red, red, 0, 0 , red, red, 0,
        red, red, purple, red, red, purple, red, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        red, purple, purple, purple, purple, purple, purple, red,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, 0, red, 0, 0, red, 0, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, red, purple, purple, purple, purple, red, 0,
        0, 0, red, purple, purple, red, 0, 0,
        0, 0, 0, red, red, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
};
