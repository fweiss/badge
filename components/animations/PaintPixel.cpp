#include "PaintPixel.h"

 PaintPixel::PaintPixel(Display &display) : BitmapAnimation(display, frames) {

 }

 void PaintPixel::setPixelColor(uint16_t x, uint16_t y, Color color) {
     frames.at(0).at(x + 8 * y) = color;
     drawFrame();
 }

std::vector<std::vector<uint32_t>> PaintPixel::frames = {
    {
      0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
    }
};
