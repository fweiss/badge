#include "HeartAnimation.h"

HeartAnimation::HeartAnimation() : BitmapAnimation(heart, 300) {

}

#define red 0x640000
#define purple 0x640064

std::vector<std::vector<uint32_t>> HeartAnimation::heart = {
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
