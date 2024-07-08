#include "IndexedColorAnimation.h"

// only implementation is template function

void IndexedColorAnimation::nextFrame() {
    frameIndex = (frameIndex + 1) % frameCount;
}
