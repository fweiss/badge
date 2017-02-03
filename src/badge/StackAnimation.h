#ifndef STACK_ANIMATION_H
#define STACK_ANIMATION_H

class StackAnimation : public Animation {
private:
//  int frame;
    uint32_t color;
protected:
    void drawFrame(unsigned long) override;
public:
    StackAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
    //    frame = 0;
        color = matrix.Color(40, 0, 0);
        setFrameCount(8);
        setRepeatCount(12);
    }
};

void StackAnimation::drawFrame(unsigned long frameIndex) {
    uint16_t x0 = 0;
    uint16_t y0 = frameIndex;
    uint16_t x1 = 7;
    uint16_t y1 = frameIndex;

    matrix.fillScreen(0);
    matrix.drawLine(x0, y0, x1, y1, color);
    matrix.show();
}

#endif STACK_ANIMATION_H
