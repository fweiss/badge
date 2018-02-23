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
    uint8_t attenuation;
    bool reverse;
    std::deque<uint32_t> *colors;
    void preroll(uint8_t amount);
protected:
public:
    ChaseGenerator(uint8_t r, uint8_t g, uint8_t b);
    uint32_t nextColor();
    void roll();
    uint32_t get(uint32_t i);
    void setReverse(bool reverse);
};

ChaseGenerator::ChaseGenerator(uint8_t r, uint8_t g, uint8_t b) {
	this->r = r;
	this->g = g;
	this->b = b;
	static const uint8_t BRIGHTEST = 1;
	static const uint8_t INDOOR = 15;
	this->attenuation = INDOOR;
	this->colors = new std::deque<uint32_t>();
	preroll(r);
	for (int i=0; i<16; i++) {
		this->colors->push_front(nextColor());
	}
	this->reverse = false;
}
void ChaseGenerator::preroll(uint8_t amount) {
	for (int i=0; i<amount; i++) {
		nextColor();
	}
}
uint32_t ChaseGenerator::nextColor() {
	// 15, 35, -25
	// 13, 37, -23
	// 3, 7, -5
	r += 3;
	g += 7;
	b += -5;
    return Adafruit_NeoPixel::Color(r/attenuation, g/attenuation, b/attenuation);
}
void ChaseGenerator::roll() {
	uint32_t nc = nextColor();
	if (reverse) {
		colors->pop_front();
    	colors->push_back(nc);
	} else {
		colors->pop_back();
		colors->push_front(nc);
	}
}
uint32_t ChaseGenerator::get(uint32_t i) {
	return this->colors->at(i);
}
void ChaseGenerator::setReverse(bool reverse) {
	this->reverse = reverse;
}


#endif CHASE_GENERATOR_H
