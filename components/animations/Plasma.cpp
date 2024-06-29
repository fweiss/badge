#include "Plasma.h"
#include <math.h>

Plasma::Plasma() : Animation(100), phase(0) {

}

struct Point {
    float x;
    float y;
};

Point lissajous(float phase, float a, float b) {
    const float rows = 8;
    const float cols = 8;
    const float scale = 1.0f;
    float x = sinf(phase * a) * scale;
    float y = sinf(phase * b) * scale;
    // scale to fit in matrix
    Point point = { (x + 1.0f) / 2.0f * rows, (y + 1.0f) / 2.0f * cols };
    // Point point = { (x + 1.0f) / 2.0f * rows, y * cols  * 0.0f };
    // Point point = { x * 0.0f * rows, (y + 1.0f) / 2.0f * cols };
    return point;
}

uint32_t xy(Point &p) {
    return (int)p.x + (int)p.y * 8;
}

void Plasma::drawFrame(Frame &frame) {
    frame.clear();
    Point p1 = lissajous(phase, 1, 1.27);
    Point p2 = lissajous(phase, 3, 4.2);
    Point p3 = lissajous(phase, 5, 3.2);

    const int p = xy(p1);
    const int r = 160;
    const int g = 150;
    const int b = 10;
    frame.setPixel(p, r, g, b);
    frame.setPixel(xy(p2), 160, 10, 10);
    frame.setPixel(xy(p3), 10, 10, 220);
    // display.update();

    frameIndex += 1;
    phase = (float)frameIndex * 0.1;
}
