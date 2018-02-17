#ifndef CHASE_GENERATOR_H
#define CHASE_GENERATOR_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
// folowing to fix Arduino.h when usinf stdlib
#undef max
#undef min
#include <deque>

class ChaseGenerator {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    bool reverse;
    std::deque<uint32_t> *colors;
protected:
public:
    ChaseGenerator(uint8_t r, uint8_t g, uint8_t b) {
    	this->r = r;
    	this->g = g;
    	this->b = b;
    	this->colors = new std::deque<uint32_t>();
    	for (int i=0; i<16; i++) {
    		this->colors->push_front(nextColor());
    	}
    	this->reverse = false;
    }
    uint32_t nextColor() {
    	r += 15;
    	g += 35;
    	b -= 25;
        return Adafruit_NeoPixel::Color(r/5, g/5, b/5);
    }
    void roll() {
    	uint32_t nc = nextColor();
    	if (reverse) {
    		colors->pop_front();
        	colors->push_back(nc);
    	} else {
			colors->pop_back();
			colors->push_front(nc);
    	}
    }
    uint32_t get(uint32_t i) {
    	return this->colors->at(i);
    }
};

#endif CHASE_GENERATOR_H
