#ifndef TICKER_ANIMATION_H
#define TICKER_ANIMATION_H

#include "Animation.h"

String utf8tocp437(String utf8);

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
        text = utf8tocp437(newText);
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

const uint16_t codes[] = {
0x00c7,
0x00fc,
0x00e9,
0x00e2,
0x00e4,
0x00e0,
0x00e5,
0x00e7,
0x00ea,
0x00eb,
0x00e8,
0x00ef,
0x00ee,
0x00ec,
0x00c4,
0x00c5,
0x00c9,
0x00e6,
0x00c6,
0x00f4,
0x00f6,
0x00f2,
0x00fb,
0x00f9,
0x00ff,
0x00d6,
0x00dc,
0x00a2,
0x00a3,
0x00a5,
0x20a7,
0x0192,
0x00e1,
0x00ed,
0x00f3,
0x00fa,
0x00f1,
0x00d1,
0x00aa,
0x00ba,
0x00bf,
0x2310,
0x00ac,
0x00bd,
0x00bc,
0x00a1,
0x00ab,
0x00bb,
0x2591,
0x2592,
0x2593,
0x2502,
0x2524,
0x2561,
0x2562,
0x2556,
0x2555,
0x2563,
0x2551,
0x2557,
0x255d,
0x255c,
0x255b,
0x2510,
0x2514,
0x2534,
0x252c,
0x251c,
0x2500,
0x253c,
0x255e,
0x255f,
0x255a,
0x2554,
0x2569,
0x2566,
0x2560,
0x2550,
0x256c,
0x2567,
0x2568,
0x2564,
0x2565,
0x2559,
0x2558,
0x2552,
0x2553,
0x256b,
0x256a,
0x2518,
0x250c,
0x2588,
0x2584,
0x258c,
0x2590,
0x2580,
0x03b1,
0x00df,
0x0393,
0x03c0,
0x03a3,
0x03c3,
0x00b5,
0x03c4,
0x03a6,
0x0398,
0x03a9,
0x03b4,
0x221e,
0x03c6,
0x03b5,
0x2229,
0x2261,
0x00b1,
0x2265,
0x2264,
0x2320,
0x2321,
0x00f7,
0x2248,
0x00b0,
0x2219,
0x00b7,
0x221a,
0x207f,
0x00b2,
0x25a0,
0x00a0
};

String utf8tocp437(String utf8) {
    String cp437 = "";
    const uint16_t error = 0xFFFD;
    uint16_t partial = 0;
    uint16_t count = 0;
    for (int i=0; i<utf8.length(); i++) {
        uint16_t next = utf8.charAt(i);
        switch (count) {
            case 0:
                if ((next & 0x80) == 0) {
                    partial = next;
                } else if ((next & 0xE0) == 0xC0) {
                    partial |= (next & 0x1F) << 6;
                    count = 1;
                } else if ((next & 0xF0) == 0xE0) {
                    partial |= (next & 0x0F) << 12;
                    count = 2;
                } else {
                    partial = error;
                }
                break;
            case 1:
                if ((next & 0xC0) == 0x80) {
                    partial |= next & 0x3F;;
                    count = 0;
                } else {
                    partial = error;
                    count = 0;
                }
                break;
            case 2:
                if ((next & 0xC0) == 0x80) {
                    partial |= (next & 0x3F) << 6;
                    count = 1;
                } else {
                    partial = error;
                    count = 0;
                }
                break;
        }
        if (count == 0) {
            if (partial < 128) {
                cp437 += (char)partial;
            } else {
                for (int j=0; j<sizeof(codes); j++) {
                    if (codes[j] == partial) {
                        cp437 += (char)(j + 128);
                    }
                }
            }
            partial = 0;
        }
    }
    return cp437;
    // if (count != 0) incomplete code
}

#endif TICKER_ANIMATION_H
