#include "Heart2.h"

Heart2::Heart2(Display &display) : BitmapAnimation(display, heart) {

}

#define purple 0x640000

std::vector<std::vector<uint32_t>> Heart2::heart = {
    {
        0, purple, purple, 0, 0 , purple, purple, 0,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        purple, purple, purple, purple, purple, purple, purple, purple,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, 0, purple, purple, purple, purple, 0, 0,
        0, 0, 0, purple, purple, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0 , 0, 0, 0,
        0, 0, purple, 0, 0, purple, 0, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, purple, purple, purple, purple, purple, purple, 0,
        0, 0, purple, purple, purple, purple, 0, 0,
        0, 0, 0, purple, purple, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    },
};
