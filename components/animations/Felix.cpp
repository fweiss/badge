#include "Felix.h"

Felix::Felix(Display& display) : BitmapAnimation(display, yy) {

}

#define back 0x8080ff
#define fur 0x000000
#define eye 0xccff00
#define tounge 0xff8080
#define paw 0xffffff

std::vector<std::vector<uint32_t>> Felix::yy = {
    {
        back, fur, back, back, fur, back, back, back,
        back, fur, fur, fur, fur, back, back, back,
        back, eye, fur, eye, fur, back, back, back,
        back, fur, fur, fur, fur, fur, back, back,
        back, back, tounge, fur, fur, fur, back, back,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, fur, fur, fur, back, fur,
        back, back, back, paw, fur, paw, fur, fur,
    }
};
