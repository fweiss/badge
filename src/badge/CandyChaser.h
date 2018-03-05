#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

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
protected:
public:
    CandyChaser(uint8_t r, uint8_t g, uint8_t b);
    CandyChaser(uint16_t size);
    virtual uint32_t nextColor() override;
};

CandyChaser::CandyChaser(uint16_t size) : Chaser(size) {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->dr = 3;
	this->dg = 7;
	this->db = -5;
	static const uint8_t BRIGHTEST = 1;
	static const uint8_t INDOOR = 15;
	this->attenuation = INDOOR;
	preroll(size);
	for (int i=0; i<16; i++) {
		this->colors->push_front(nextColor());
	}
	this->setReverse(true);
}

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

uint32_t CandyChaser::nextColor() {
	// 15, 35, -25
	// 13, 37, -23
	// 3, 7, -5
	r += dr;
	g += dg;
	b += db;
    return Adafruit_NeoPixel::Color(r/attenuation, g/attenuation, b/attenuation);
}
