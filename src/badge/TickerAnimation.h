#ifndef TICKERANIMATION_H
#define TICKERANIMATION_H

#include "Animation.h"


class TickerAnimation : public Animation {
private:
  unsigned long scrollOffset;
  unsigned long scrollLength;
protected:
  String text;
  void draw() override;
  const int pixelsPerChar = 6;
public:
  uint32_t textBackgroundColor;
  uint32_t textColor;
  void setText(String newText) {
    text = newText;
    scrollOffset = 0;
    scrollLength = (text.length() + 2) * pixelsPerChar;
  }
  void setTextColor(uint32_t color) {
    textColor = color;
  }
  void setTextColor(byte r, byte g, byte b) {
    setTextColor(matrix.Color(r, g, b));
  }
  TickerAnimation(Adafruit_NeoMatrix &m) : Animation(m) {
    setText("strong");
    textBackgroundColor = matrix.Color(0, 0, 0);
    textColor = matrix.Color(0, 60, 0);
  }  
};

void TickerAnimation::draw() {
  matrix.fillScreen(textBackgroundColor);
  matrix.setTextColor(textColor);
  matrix.setTextWrap(false);
  matrix.setCursor(pixelsPerChar - scrollOffset, 0); // dwell to scroll in first char
  matrix.print(text);
  matrix.show();     
  scrollOffset = (scrollOffset + 1) % scrollLength;
}

#endif TICKERANIMATION_H



