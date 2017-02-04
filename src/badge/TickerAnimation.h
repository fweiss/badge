#ifndef TICKER_ANIMATION_H
#define TICKER_ANIMATION_H

#include "Animation.h"

// experimental UTF-8 conversion, still needs CP437 conversion
static byte blast;
byte utf8ascii(byte src) {
    if (src < 128) {
        return src;
    }
    byte last = blast;
    blast = src;
    switch (last) {
        case 0xC2:
            return src;
        case 0xC3:
            return 0xC0 | src;
        case 0x82:
            if (src == 0xAC) return 0xEE; // euro symbol
    }
    return 0;
}

String utf8ascii(String src) {
    String dst = "";
    char c;
    for (int i=0; i< src.length(); i++) {
        c = utf8ascii(src.charAt(i));
        if (c != 0)
            dst += c;
    }
    return dst;
}

class TickerAnimation : public Animation {
private:
    unsigned long scrollOffset;
    unsigned long scrollLength;
protected:
    String text;
    void drawFrame(unsigned long) override;
    const int pixelsPerChar = 6;
public:
    uint32_t textBackgroundColor;
    uint32_t textColor;
    void setText(String newText) {
        text = utf8ascii(newText);
        scrollOffset = 0;
        scrollLength = (text.length() + 2) * pixelsPerChar;
        setFrameCount(scrollLength);
        start();
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
        matrix.cp437(true); // to get around legacy bug in gfx
    }
};

void TickerAnimation::drawFrame(unsigned long frameIndex) {
    matrix.fillScreen(textBackgroundColor);
    matrix.setTextColor(textColor);
    matrix.setTextWrap(false);
    matrix.setCursor(pixelsPerChar - frameIndex, 0); // dwell to scroll in first char
    matrix.print(text);
    matrix.show();
 }


#endif TICKER_ANIMATION_H
