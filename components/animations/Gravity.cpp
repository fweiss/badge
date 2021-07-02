#include "Gravity.h"

#include <math.h>

Gravity::Gravity(Display &display) : Animation(display, 100) {
    this->motionData = { 0.0, 0.0, 0.0 };
}

int b(float x) {
    if (x > 7) x = 7;
    if (x < 0) x = 0;
    return x;
}

void Gravity::drawFrame() {
    display.clear();

    // debug verify addressing
    // int p = this->x + (8 * this->y);
    // display.setPixel(p, 10, 10, 160);
    // this->x = (this->x + 1) % 8;
    // if (this->x == 0) {
    //     this->y = (this->y + 1) % 8;
    // }

    const float ax = this->motionData.ax;
    const float ay = this->motionData.ay;

    // float r = sqrt(ax * ax + ay * ay);
    // float angle = atan2(this->motionData.ay, this->motionData.ax);
    // float r *= 4.2; // empirical to reach corners 
    // float dx = r * cos(angle);
    // float dy = r * - sin(angle); // top-down

    float r = 4.7;
    float dx = r * ax;
    float dy = r * - ay;

    int ox = b(3.5 + dx);
    int oy = b(3.5 + dy);
    printf("offsets %d, %d\n", ox, oy);

    int offset = ox + 8 * oy;
    if (offset > 63) {
        offset = 63;
    }
    display.setPixel(offset, 10, 160, 10);

    display.update();
}

void Gravity::setMotion(MotionData motionData) {
    this->motionData = motionData;
}
