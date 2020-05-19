#include "Tween.h"

Tween::Tween(Display &display) : BitmapAnimation(display, frames, 500) {

}

uint32_t scale(uint32_t source, float factor) {
	uint8_t r = (source & 0xff) * factor;
	uint8_t g = (source >> 8 & 0xff) * factor;
	uint8_t b = (source >> 16 & 0xff) * factor;
	return r | g << 8 | b << 16;
}

static uint32_t tween(std::vector<uint32_t> frame, uint16_t r, uint16_t c) {
	// pointers to the source pixels
	uint32_t *qq[3][3] = { };
	for (int i=-1; i<2; i++) {
		for (int j=-1; j<2; j++) {
			bool bounds = r + i >= 0 && r + i < 8 && c + j >= 0 && c + j < 8;
			qq[i+1][j+1] = bounds ? &frame[8 * (r + i) + (c + j)] : 0;
		}
	}

	// 9x9 tween factors
	float ff[3][3] = { 0, 0, 0, .2, .6, .2, 0, 0, 0 };
//	float ff[3][3] = { .05, .10, .05, .10, 1.0 - 0.6, .10, .05, .10, .05 };
//	float ff[3][3] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	// pointer to middle with 2d array  comprehension
	float (*f)[3] = (float (*)[3]) &ff[1][1];

	// offset pointers to middle of 9x9
	uint32_t *(*q)[3] = (uint32_t* (*)[3]) &qq[1][1];


	// do the dot product
	// N.B. x[i][j] = *(&x + 3 * i + j)
	uint32_t p = 0;
	for (int i=-1; i<2; i++) {
		for (int j=-1; j<2; j++) {
//			if (q[i][j]) p += *q[i][j] * f[i][j];
			if (q[i][j]) p += scale(*q[i][j], f[i][j]);
		}
	}
	return p;
}

void Tween::drawFrame(uint16_t frameIndex) {
    std::vector<uint32_t> frame = frames.at(0);
    uint16_t shift = frameIndex % 8;
    uint16_t p = 0;
//    for (uint32_t c : frame) {
    for (int16_t i=0; i<frame.size(); i++) {
    	uint32_t c = frame[i];
    	uint16_t row = p / 8;
    	uint16_t col = p % 8;
    	p++;
    	uint16_t index = row * 8 + ((col + shift) % 8);
        display.setPixel(index, tween(frame, row, col));
    }
    display.update();
}

//void Tween::drawFrame(uint16_t frameIndex) {
//    std::vector<uint32_t> frame = frames.at(0);
//    uint16_t shift = frameIndex % 8;
//    uint16_t p = 0;
////    for (uint32_t c : frame) {
//    for (int16_t i=0; i<frame.size(); i++) {
//    	uint32_t c = frame[i];
//    	uint16_t row = p / 8;
//    	uint16_t col = p % 8;
//    	p++;
//    	uint16_t index = row * 8 + ((col + shift) % 8);
//        display.setPixel(index, c);
//    }
//    display.update();
//}


BitmapAnimation::Frames Tween::frames = {
//        A

        {0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        B

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        C

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        D

        {0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},


//        E

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        F

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        G

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        H

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        I

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        J

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        K

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        L

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        M

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        N

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        O

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        P

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        Q

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        R

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        S

        {0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        T

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        U

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        V

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        W

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        X

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        Y

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        Z

        {0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},


//        a

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        b

        {0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        c

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        d

        {0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},


//        e

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        f

        {0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        g

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000},

//        h

        {0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        i

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        j

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000},

//        k

        {0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        l

        {0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        m

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        n

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        o

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        p

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        q

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000},

//        r

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        s

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        t

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        u

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        v

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        w

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0xffffff,0x000000,0xffffff,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        x

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

//        y

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000},

//        z

        {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
};
