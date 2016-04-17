#ifndef STACKANIMATION_H
#define STACKANIMATION_H

class StackAnimation : public Animation {
private:
  int frame;
  uint32_t color;
protected:
  void draw() override;
public:
  StackAnimation(Adafruit_NeoMatrix &matrix) : Animation(matrix) {
    frame = 0; 
    color = matrix.Color(40, 0, 0);
  }
};

void StackAnimation::draw() {
  uint16_t x0 = 0;
  uint16_t y0 = frame;
  uint16_t x1 = 7;
  uint16_t y1 = frame;
  
  matrix.fillScreen(0);
  matrix.drawLine(x0, y0, x1, y1, color);
  frame = (frame + 1) % 8;
}


#endif STACKANIMATION_H

