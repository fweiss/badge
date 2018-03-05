#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Animation {
private:
    unsigned long lastTime;
    unsigned long period;
    unsigned long frameIndex = 0;
    unsigned long frameCount = 1;
    unsigned long repeatIndex = 0;
    unsigned long repeatCount = 1;
    bool running = false;
    bool enabled = false;
    uint32_t backgroundColor = 0;
protected:
    Adafruit_NeoMatrix &matrix;
    void setFrameCount(unsigned long frameCount);
    void setRepeatCount(unsigned long repeatCount);
    virtual void draw() {}
    virtual void drawFrame(unsigned long frameIndex) { (void)frameIndex; }
public:
    Animation(Adafruit_NeoMatrix &matrix);
    virtual ~Animation() {};
    void setPeriod(unsigned long p);
    void start();
    void stop();
    boolean isRunning();
    boolean isEnabled();
    void enable(boolean enabled);
    void update(unsigned long now);
    void updateFrame();

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
    static uint32_t createColor32(uint8_t r, uint8_t g, uint8_t b) {
        return Adafruit_NeoPixel::Color(r, g, b);
    }
    static uint16_t createColor16(uint8_t r, uint8_t g, uint8_t b) {
        return Adafruit_NeoMatrix::Color(r, g, b);
    }
};

Animation::Animation(Adafruit_NeoMatrix &m) : matrix(m) {
    lastTime = 0;
    period = 100;
}

void Animation::update(unsigned long now) {
    if (lastTime == 0 || (running &&  now >= lastTime + period)) {
        lastTime = now;
        updateFrame();
        draw();
    }
}

void Animation::updateFrame() {
    drawFrame(frameIndex);
    frameIndex = (frameIndex + 1) % frameCount;
    if (frameIndex == 0) {
        repeatIndex = (repeatIndex + 1) % repeatCount;
        if (repeatIndex == 0) {
        running = false;
        }
    }
}
void Animation::setPeriod(unsigned long p) {
    period = p;
}
void Animation::start() {
    running = true;
    enabled = true;
    frameIndex = 0;
    repeatIndex = 0;
}
void Animation::stop() {
    running = false;
    enabled = false;
    matrix.fillScreen(backgroundColor);
    matrix.show();
}
boolean Animation::isRunning() {
    return running;
}
boolean Animation::isEnabled() {
    return enabled;
}
void Animation::enable(boolean enabled) {
	this->enabled = enabled;
}
void Animation::setFrameCount(unsigned long frameCount) {
    this->frameCount = frameCount;
}
void Animation::setRepeatCount(unsigned long repeatCount) {
    this->repeatCount = repeatCount;
}



