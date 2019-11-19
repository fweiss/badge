#include "BitmapAnimation.h"

BitmapAnimation::BitmapAnimation(Display &display) :
    Animation(display) {

}

void BitmapAnimation::drawFrame() {
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            uint16_t  p = y * 8 + x;
//            uint32_t c = 0x882266;
            uint32_t c = bitmap[x][y];
            display.setPixel(p, c);
        }
    }
    display.update();
}

#define back 0x8080ff
#define fur 0x000000
#define eye 0xccff00
#define tounge 0xff8080
#define paw 0xffffff

uint32_t BitmapAnimation::bitmap[8][8] = {
             { back, fur, back, back, fur, back, back, back },
             { back, fur, fur, fur, fur, back, back, back },
             { back, eye, fur, eye, fur, back, back, back },
             { back, fur, fur, fur, fur, fur, back, back },
             { back, back, tounge, fur, fur, fur, back, back },
             { back, back, back, fur, fur, fur, back, fur },
             { back, back, back, fur, fur, fur, back, fur },
             { back, back, back, paw, fur, paw, fur, fur }
};
