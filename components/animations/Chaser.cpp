#include "Chaser.h"

Chaser::Chaser(uint16_t size) : colors(size) {
//	this->colors = new std::deque<uint32_t>(size);
    this->reverse = false;
}

void Chaser::roll() {
    uint32_t nc = nextColor();
    if (reverse) {
        colors.pop_back();
        colors.push_front(nc);
    } else {
        colors.pop_front();
        colors.push_back(nc);
    }
}

void Chaser::setReverse(bool reverse) {
    this->reverse = reverse;
}

uint32_t Chaser::get(uint16_t index) {
    return colors.at(index);
}

void Chaser::preroll(uint16_t amount) {
    for (int i=0; i<amount; i++) {
        nextColor();
    }
}

