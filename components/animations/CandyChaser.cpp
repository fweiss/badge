#include "CandyChaser.h"

CandyChaser::CandyChaser(uint16_t size) : Chaser(size) {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->dr = 3;
	this->dg = 7;
	this->db = -5;
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
//    return Adafruit_NeoPixel::Color(r/attenuation, g/attenuation, b/attenuation);
	return createRgbColor(r, g, b);
}
