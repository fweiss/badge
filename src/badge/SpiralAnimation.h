#ifndef SPIRAL_ANIMATION_H
#define SPIRAL_ANIMATION_H

#include "BitmapAnimation.h"
// folowing to fix Arduino.h when usinf stdlib
#undef max
#undef min
#include <vector>

class Generator {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
protected:
public:
    Generator(uint8_t r, uint8_t g, uint8_t b) {
    	this->r = r;
    	this->g = g;
    	this->b = b;
    }
    uint32_t nextColor() {
    	r += 3;
    	g += 7;
    	b -= 5;
        return Adafruit_NeoPixel::Color(r/3, g/3, b/3);
    }
};

class SpiralAnimation : public PixelAnimation {
private:
    static const byte bits[];
    void drawPixels2(std::vector<int> pixels, Generator *generator);
    uint32_t currentColor;
    uint32_t nextColor();
    Generator* generator0;
    Generator* generator1;
    Generator* generator2;
    Generator* generator3;
protected:
    void drawFrame(unsigned long frameIndex) override;
public:
    SpiralAnimation(Adafruit_NeoMatrix &matrix) : PixelAnimation(matrix) {
        setRepeatCount(80);
        currentColor = Adafruit_NeoPixel::Color(60, 0, 0);
        generator0 = new Generator(10, 0, 0);
        generator1 = new Generator(0, 10, 0);
        generator2 = new Generator(0, 0, 10);
        generator3 = new Generator(10, 10, 0);
    }
};

// see https://forum.pjrc.com/threads/23467-Using-std-vector?p=69787&viewfull=1#post69787
namespace std {
  void __throw_bad_alloc()
  {
    Serial.println("Unable to allocate memory");
  }

  void __throw_length_error( char const*e )
  {
    Serial.print("Length Error :");
    Serial.println(e);
  }
}

void SpiralAnimation::drawFrame(unsigned long frameIndex) {
	static const std::vector<int> spiral0 = {0, 1, 2, 3, 4, 5, 6, 14, 22, 30, 38, 46, 45, 44, 43, 35};
	static const std::vector<int> spiral1 = {7, 15, 23, 31, 39, 47, 55, 54, 53, 52, 51, 50, 42, 34, 26, 27};
	static const std::vector<int> spiral2 = {63, 62, 61, 60, 59, 58, 57, 49, 41, 33, 25, 17, 18, 19, 20, 28};
	static const std::vector<int> spiral3 = {56, 48, 40, 32, 24, 16, 8, 9, 10, 11, 12, 13, 21, 29, 37, 36};

	static const uint32_t color0 = Adafruit_NeoPixel::Color(60, 0, 0);
	static const uint32_t color1 = Adafruit_NeoPixel::Color(60, 40, 0);
	static const uint32_t color2 = Adafruit_NeoPixel::Color(0, 60, 0);
	static const uint32_t color3 = Adafruit_NeoPixel::Color(0, 0, 60);

	drawPixels2(spiral0, generator0);
	drawPixels2(spiral1, generator1);
	drawPixels2(spiral2, generator2);
	drawPixels2(spiral3, generator3);
    matrix.show();
}

void SpiralAnimation::drawPixels2(std::vector<int> spiral, Generator *generator) {
	uint32_t nc = generator->nextColor();
	for(int n : spiral) {
		matrix.setPixelColor(n, nc);
	}
}

#endif SPIRAL_ANIMATION_H
