#ifndef AUM_ANIMATION_H
#define AUM_ANIMATION_H

#include "BitmapAnimation.h"

class AumAnimation : public BitmapAnimation {
private:
    static const byte bits[];
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    AumAnimation(Adafruit_NeoMatrix &matrix) : BitmapAnimation(matrix) {
        setRepeatCount(80);
    }
};

const byte AumAnimation::bits[] = {
    0b00101010,
    0b00011100,
    0b01110000,
    0b00001010,
    0b00110101,
    0b00001001,
    0b10001010,
    0b01110000,
};

void AumAnimation::drawFrame(unsigned long frameIndex) {
    uint32_t color = matrix.Color(20, 20, 40);
    matrix.clear();
    drawBitmap(bits, color);
    matrix.show();
}

#endif AUM_ANIMATION_H
