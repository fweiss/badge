#include "SpinBottleAnimation.h"

SpinBottleAnimation::SpinBottleAnimation(Display &display) : BitmapAnimation(display, frames) {

}

std::vector<std::vector<uint32_t>> SpinBottleAnimation::frames = {


//bright green
//hsv(109, 80%, 92%)
//
//darker green
//hsv(138, 87%, 40%)
//
//dark green gray
//hsv(138, 54%, 38%)
//
//Black
//hsv(0, 0%, 0%)


//SE - Arrow

{0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f},

//E - Arrow

{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f},

//NE - Arrow

{0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x2d613c,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//N - Arrow

{0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x51eb2f,0x2d613c,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000},

//NW - Arrow

{0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f},

//W - Arrow

{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x2d613c,0x2d613c,0x2d613c,0x2d613c,0x2d613c,0x2d613c,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x51eb2f,0x2d613c,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//SW - Arrow

{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000},

//S - Arrow

{0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x51eb2f,0x000000,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x51eb2f,0x51eb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x51eb2f,0x000000,0x000000,0x000000},


};
