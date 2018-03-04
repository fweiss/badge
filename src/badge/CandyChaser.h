#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
// folowing to fix Arduino.h when usinf stdlib
#undef max
#undef min
#include <deque>

#include "Chaser.h"

class CandyChaser : public Chaser {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t dr;
    uint8_t dg;
    uint8_t db;
    uint8_t attenuation;
    void preroll(uint8_t amount);
protected:
public:
    CandyChaser(uint8_t r, uint8_t g, uint8_t b);
    virtual uint32_t nextColor() override;
};

CandyChaser::CandyChaser(uint8_t r, uint8_t g, uint8_t b) : Chaser(16) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->dr = 3;
	this->dg = 7;
	this->db = -5;
	static const uint8_t BRIGHTEST = 1;
	static const uint8_t INDOOR = 15;
	this->attenuation = INDOOR;
	this->colors = new std::deque<uint32_t>();
	preroll(r);
	for (int i=0; i<16; i++) {
		this->colors->push_front(nextColor());
	}
	this->setReverse(true);
}
void CandyChaser::preroll(uint8_t amount) {
	for (int i=0; i<amount; i++) {
		nextColor();
	}
}
uint32_t CandyChaser::nextColor() {
	// 15, 35, -25
	// 13, 37, -23
	// 3, 7, -5
	r += dr;
	g += dg;
	b += db;
    return Adafruit_NeoPixel::Color(r/attenuation, g/attenuation, b/attenuation);
}
