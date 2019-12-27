#include "PaintPixel.h"

 PaintPixel::PaintPixel(Display &display) : BitmapAnimation(display, frames) {

 }

 void PaintPixel::setPixelColor(uint16_t x, uint16_t y, Color color) {
     frames.at(0).at(x + 8 * y) = color;
     drawFrame();
 }

#define back 0x000000
#define fur 0xe8bc50
#define eye 0x53befb
#define tounge 0xff8080
#define paw 0xffffff

std::vector<std::vector<uint32_t>> PaintPixel::frames = {
    {
        back, fur, back, back, fur, back, back, back,
        back, fur, fur, fur, fur, back, back, back,
        back, eye, fur, eye, fur, back, back, back,
        back, fur, fur, fur, fur, fur, back, back,
        back, back, tounge, fur, fur, fur, back, fur,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, paw, fur, paw, fur, back,
    }
};
