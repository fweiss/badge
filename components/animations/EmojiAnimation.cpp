#include "EmojiAnimation.h"

EmojiAnimation::EmojiAnimation() : BitmapAnimation(frames, 2000) {

}

std::vector<std::vector<uint32_t>> EmojiAnimation::frames = {
//        No smile

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},


//        Smile

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},


//        Big smile

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Oh!, Open mouth, or Yawn, or OMG

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Frown

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Big Mouth

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Open Mouth

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Single Tear

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x2fe4eb,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},

//        Crying

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x2fe4eb,0x000000,0x000000,0x2fe4eb,0x000000,0xebeb2f,0xebeb2f,0x2fe4eb,0x000000,0x000000,0x000000,0x000000,0x2fe4eb,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000},


//        Little Angry

        {0x000000,0x000000,0xeb2f2f,0xeb2f2f,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0xeb2f2f,0xeb2f2f,0x000000,0x000000},

//        Very Mad

        {0x000000,0x000000,0xeb2f2f,0xeb2f2f,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0xeb2f2f,0xeb2f2f,0xeb2f2f,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0x000000,0xeb2f2f,0x000000,0x000000,0x000000,0xeb2f2f,0xeb2f2f,0xeb2f2f,0xeb2f2f,0x000000,0x000000},

//        Stick Out Tongue

        {0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0x000000,0xebeb2f,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0x000000,0xebeb2f,0xebeb2f,0x000000,0xebeb2f,0xeb2f2f,0xeb2f2f,0xebeb2f,0x000000,0xebeb2f,0x000000,0xebeb2f,0x000000,0xeb2f2f,0xeb2f2f,0x000000,0xebeb2f,0x000000,0x000000,0x000000,0xebeb2f,0xebeb2f,0xebeb2f,0xebeb2f,0x000000,0x000000}


};
