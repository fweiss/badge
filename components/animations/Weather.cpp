#include "Weather.h"

Weather::Weather(Display &display) : BitmapAnimation(display, frames, 2000) {

}

BitmapAnimation::Frames Weather::frames = {
//        Bright Sun

        {0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffff00,0xffff00,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xff9900,0xff9900,0xffff00,0xffffff,0xffffff,0xffff00,0xff9900,0xff9900,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffff00,0xffff00,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff},

//        Sun 2

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffff00,0xffff00,0x000000,0x000000,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0xffff00,0xff9900,0xff9900,0xffff00,0x000000,0x000000,0x000000,0x000000,0x000000,0xffff00,0xffff00,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        Rain Cloud

        {0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x00ffff,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ffff,0x000000,0x00ffff,0x000000,0x000000,0x000000,0x00ffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ffff,0x000000,0x00ffff,0x000000,0x000000},


//        Sun & Cloud

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff9900,0xff9900,0x000000,0x000000,0x000000,0x000000,0x000000,0xff9900,0xffff00,0xffff00,0xff9900,0x000000,0x000000,0x000000,0x000000,0xff9900,0xffff00,0xffff00,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xff9900,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000}

};