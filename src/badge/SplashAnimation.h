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
    uint16_t color = createColor16(5, 5, 30);
    matrix.clear();
    drawBitmap(bits, color);
    matrix.show();
}

#endif SPLASH_ANIMATION_H
