#ifndef TICKERANIMATION_H
#define TICKERANIMATION_H

#include "Animation.h"

const int PIXELS_PER_CHAR = 6;

class TickerAnimation : public Animation {
protected:
  String text;
  unsigned long offset;
  void draw() override;
public:
  uint32_t textBackgroundColor;
  uint32_t textColor;
  void setText(String newText) {
    text = newText;
    offset = 0;
  }
  void setTextColor(uint32_t color) {
    textColor = color;
  }
  TickerAnimation(Adafruit_NeoMatrix &m) : Animation(m) {
    text = "strong";
    offset = 0;
    textBackgroundColor = matrix.Color(0, 0, 0);
    textColor = matrix.Color(40, 0, 0);
  }  
};

void TickerAnimation::draw() {
  matrix.fillScreen(textBackgroundColor);
  matrix.setTextColor(textColor);
  matrix.setCursor(-offset, 0);
  matrix.print(text);
  matrix.show();
  offset = (offset + 1) % (text.length() * PIXELS_PER_CHAR);      
}

#endif TICKERANIMATION_H



