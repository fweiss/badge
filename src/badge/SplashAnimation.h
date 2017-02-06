#ifndef SPLASH_ANIMATION_H
#define SPLASH_ANIMATION_H

#include "BitmapAnimation.h"

class SplashAnimation : public BitmapAnimation {
private:
    static const byte bits[];
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    SplashAnimation(Adafruit_NeoMatrix &matrix) : BitmapAnimation(matrix) {
        setFrameCount(10);
        setRepeatCount(80);
    }
};

const byte SplashAnimation::bits[] = {
    0b00010000,
    0b00011000,
    0b01010100,
    0b00111000,
    0b00111000,
    0b01010100,
    0b00011000,
    0b00010000,
};

void SplashAnimation::drawFrame(unsigned long frameIndex) {
    unsigned long sawtooth = abs((signed long)frameIndex - 5);
    uint8_t r = map(sawtooth, 0, 5, 5, 10);
    uint8_t g = map(sawtooth, 0, 5, 5, 10);
    uint8_t b = map(sawtooth, 0, 5, 5, 35);
    uint16_t color = createColor16(0, 0, b);
    matrix.clear();
    drawBitmap(bits, color);
    matrix.show();
}

#endif SPLASH_ANIMATION_H
