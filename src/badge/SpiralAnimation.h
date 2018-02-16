#ifndef SPIRAL_ANIMATION_H
#define SPIRAL_ANIMATION_H

#include "BitmapAnimation.h"

class SpiralAnimation : public PixelAnimation {
private:
    static const byte bits[];
    void drawPixels2(const int* pixels, uint32_t color);
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    SpiralAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix) {
        setRepeatCount(80);
    }
};

void SpiralAnimation::drawFrame(unsigned long frameIndex) {
//    drawPixels2(frames[(frameIndex + 0) % frameCount], colors[0]);
}

void SpiralAnimation::drawPixels2(const int* pixels, uint32_t color) {
    for (int i=0; i<pixels[0]; i++) {
        matrix.setPixelColor(pixels[i + 1], color);
    }
    matrix.show();
}

#endif SPIRAL_ANIMATION_H
