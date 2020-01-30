#include "PaintPixel.h"

 PaintPixel::PaintPixel(Display &display) : BitmapAnimation(display, frames) {

 }

 void PaintPixel::setPixelColor(uint16_t x, uint16_t y, Color color) {
     frames.at(0).at(x + 8 * y) = color;
     drawFrame();
 }

 void PaintPixel::clearFrames() {
     frames.clear();
 }

 void PaintPixel::setFrame(std::vector<uint32_t> frame) {
     frames.push_back(frame);
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
