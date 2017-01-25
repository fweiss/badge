#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Animation {
private:
    unsigned long lastTime;
    unsigned long period;
    bool running = false;
protected:
    Adafruit_NeoMatrix &matrix;
    virtual void draw() {
    }
public:
    Animation(Adafruit_NeoMatrix &matrix);
    void start() {
        running = true;
    }
    void stop() {
        running = false;
    }
    boolean isRunning() {
        return running;
    }
    void update(unsigned long now) {
        if (lastTime == 0 || running &&  now >= lastTime + period) {
            lastTime = now;
            draw();
        }
    }
    uint32_t hsv(byte h, byte s, byte v) {
        if (s == 0) {
            return matrix.Color(v, v, v);
        }
        if (h < 64) {
            return matrix.Color(20, 20, 20);
        }
        if (h < 128) {
            return matrix.Color(20, 20, 20);
        }
        if (h < 192) {
            return matrix.Color(20, 20, 20);
        }
        return matrix.Color(20, 20, 20);
    }
};

Animation::Animation(Adafruit_NeoMatrix &m) : matrix(m) {
    lastTime = 0;
    period = 100;
}

#endif ANIMATION_H
