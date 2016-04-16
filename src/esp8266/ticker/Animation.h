#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

const int PIXELS_PER_CHAR = 6;

class Animation {
private:
  Adafruit_NeoMatrix *matrix;
  unsigned long lastTime;
  unsigned long period;
  String text;
  unsigned long offset;
public:
  uint32_t textBackgroundColor;
  uint32_t textColor;
  Animation(Adafruit_NeoMatrix *matrix);
  void setText(String newText) {
    text = newText;
    offset = 0;
  }
  void update(unsigned long now) {
    if (now >= lastTime + period) {
      lastTime = now;
      matrix->fillScreen(textBackgroundColor);
      matrix->setCursor(-offset, 0);
      matrix->print(text);
      matrix->show();
      offset = (offset + 1) % (text.length() * PIXELS_PER_CHAR);      
    }
  }
};

Animation::Animation(Adafruit_NeoMatrix *m) {
  matrix = m;
  lastTime = 0;
  period = 100;
  text = "strong";
  offset = 0;
  textBackgroundColor = matrix->Color(0, 0, 0);
  textColor = matrix->Color(40, 0, 0);
}

