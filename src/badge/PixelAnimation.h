#ifndef PIXEL_ANIMATION_H
#define PIXEL_ANIMATION_H

#include "Animation.h"

class PixelAnimation : public Animation {
private:
    // pixel indices of various sized squares
    static const int p1[];
    static const int p2[];
    static const int p3[];
    static const int p4[];
    static const int* frames[];
    int frameIndex = 0;
    int frameCount = 4;
    uint32_t colors[4];
    void drawPixels(const int*, uint32_t);
protected:
    void drawFrame(unsigned long) override;
public:
    PixelAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
        setPeriod(40);
        colors[0] = Adafruit_NeoPixel::Color(60, 0, 0);
        colors[1] = Adafruit_NeoPixel::Color(60, 40, 0);
        colors[2] = Adafruit_NeoPixel::Color(0, 60, 0);
        colors[3] = Adafruit_NeoPixel::Color(0, 0, 60);
        setFrameCount(4);
        setRepeatCount(20);
    }
};

const int PixelAnimation::p1[] = { 4, 27, 28, 35, 36 };
const int PixelAnimation::p2[] = { 12, 18, 19, 20, 21, 26, 29, 34, 37, 42, 43, 44, 45 };
const int PixelAnimation::p3[] = { 20, 9, 10, 11, 12, 13, 14, 17, 22, 25, 30, 33, 38, 41, 46, 49, 50, 51, 52, 53, 54 };
const int PixelAnimation::p4[] = { 28, 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 23, 24, 31, 32, 39, 40, 47, 48, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
const int* PixelAnimation::frames[] = { p1, p2, p3, p4, p3, p2 };

void PixelAnimation::drawFrame(unsigned long frameIndex) {
    drawPixels(frames[(frameIndex + 0) % frameCount], colors[0]);
    drawPixels(frames[(frameIndex + 1) % frameCount], colors[1]);
    drawPixels(frames[(frameIndex + 2) % frameCount], colors[2]);
    drawPixels(frames[(frameIndex + 3) % frameCount], colors[3]);
}

void PixelAnimation::drawPixels(const int* pixels, uint32_t color) {
    for (int i=0; i<pixels[0]; i++) {
        matrix.setPixelColor(pixels[i + 1], color);
    }
    matrix.show();
}

#endif PIXEL_ANIMATION_H

