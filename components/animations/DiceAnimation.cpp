#include "DiceAnimation.h"

DiceAnimation::DiceAnimation() : IndexedColorAnimation(2000) {
    IndexedColorAnimation::setFrameCount(pixelIndexes);
}

void DiceAnimation::drawFrame(Frame &frame) {
    IndexedColorAnimation::drawFrame(frame, colorMap, pixelIndexes);
}

std::map<DiceAnimation::ColorIndex,uint32_t> DiceAnimation::colorMap = {
        {black, 0x000000},
        {white, 0xffffff}
};

DiceAnimation::ColorIndex DiceAnimation::pixelIndexes[6][64]{
//        1 Die

        {black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},

//        2 Die

        {white,white,black,black,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black,black,white,white},

//        3 Die

        {white,white,black,black,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black,black,white,white},

//        4 Die

        {white,white,black,black,black,black,white,white,white,white,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,white,white,white,white,black,black,black,black,white,white},

//        5 Die

        {white,white,black,black,black,black,white,white,white,white,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black,black,white,white,black,black,black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,white,white,white,white,black,black,black,black,white,white},

//        6 Die

        {black,white,white,black,black,white,white,black,black,white,white,black,black,white,white,black,black,black,black,black,black,black,black,black,black,white,white,black,black,white,white,black,black,white,white,black,black,white,white,black,black,black,black,black,black,black,black,black,black,white,white,black,black,white,white,black,black,white,white,black,black,white,white,black}

};
