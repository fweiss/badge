#include "EmojiAnimation.h"

EmojiAnimation::EmojiAnimation() : IndexedColorAnimation(2000) {
    IndexedColorAnimation::setFrameCount(pixelIndexes);
}

void EmojiAnimation::drawFrame(Frame& frame) {
    IndexedColorAnimation::drawFrame(frame, colorMap, pixelIndexes);
}

std::map<EmojiAnimation::ColorIndex,uint32_t> EmojiAnimation::colorMap{
    { back, 0x000000 },
    { fore, 0xebeb2f },
    { tear, 0x2fe4eb },
    { anger, 0xeb2f2f },
    { tongue, 0xFF00FF },
};

EmojiAnimation::ColorIndex EmojiAnimation::pixelIndexes[12][64]{
//        No smile

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},


//        Smile

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,fore,back,back,fore,back,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},


//        Big smile

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,fore,fore,fore,fore,back,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Oh!, Open mouth, or Yawn, or OMG

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,fore,fore,back,back,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Frown

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,fore,fore,fore,fore,back,fore,fore,back,fore,back,back,fore,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Big Mouth

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,fore,fore,fore,fore,back,fore,fore,back,fore,fore,fore,fore,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Open Mouth

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,fore,fore,back,back,fore,fore,back,fore,back,back,fore,back,fore,back,fore,back,fore,fore,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Single Tear

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,tear,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},

//        Crying

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,tear,back,back,tear,back,fore,fore,tear,back,back,back,back,tear,fore,fore,back,back,fore,fore,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back},


//        Little Angry

        {back,back,anger,anger,anger,anger,back,back,back,anger,back,back,back,back,anger,back,anger,back,anger,back,back,anger,back,anger,anger,back,back,back,back,back,back,anger,anger,back,back,anger,anger,back,back,anger,anger,back,anger,back,back,anger,back,anger,back,anger,back,back,back,back,anger,back,back,back,anger,anger,anger,anger,back,back},

//        Very Mad

        {back,back,anger,anger,anger,anger,back,back,back,anger,back,back,back,back,anger,back,anger,back,anger,back,back,anger,back,anger,anger,back,back,back,back,back,back,anger,anger,back,back,anger,anger,back,back,anger,anger,back,anger,anger,anger,anger,back,anger,back,anger,back,back,back,back,anger,back,back,back,anger,anger,anger,anger,back,back},

//        Stick Out Tongue

        {back,back,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,fore,back,fore,fore,back,back,back,back,back,back,fore,fore,back,back,fore,fore,back,back,fore,fore,back,fore,anger,anger,fore,back,fore,back,fore,back,anger,anger,back,fore,back,back,back,fore,fore,fore,fore,back,back}


};
