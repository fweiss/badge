#pragma once

#include <deque>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

class Chaser {
public:
	Chaser(uint16_t size);
	void roll();
	virtual uint32_t nextColor() = 0;
	void setReverse(bool reverse);
	uint32_t get(uint16_t index);
protected:
	std::deque<uint32_t> *colors;
private:
	bool reverse;
};

Chaser::Chaser(uint16_t size) {
	this->colors = new std::deque<uint32_t>(size);
	this->reverse = false;
}

void Chaser::roll() {
	uint32_t nc = nextColor();
	if (reverse) {
		colors->pop_front();
    		colors->push_back(nc);
	} else {
		colors->pop_back();
		colors->push_front(nc);
	}
}

void Chaser::setReverse(bool reverse) {
	this->reverse = reverse;
}

uint32_t Chaser::get(uint16_t index) {
	return colors->at(index);
}