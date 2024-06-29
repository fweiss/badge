#include "MarqueeAnimation.h"

MarqueeAnimation::MarqueeAnimation() : PathAnimation(100), chaser(8, 256 * 3 / 8) {
    chaser.preroll(8);
    chaser.setReverse(true);
}
void MarqueeAnimation::drawFrame(Frame &frame) {
    uint16_t row = 0;
    for (std::vector<uint16_t> path : paths) {
        uint16_t chaserIndex = 0;
        for (uint16_t pixelIndex : path) {
            uint32_t color = chaser.get(chaserIndex++);
            bool black = 0 == ((chaserIndex + frameIndex) % 3);
            frame.setPixel(pixelIndex, black ? 0 : color);
        }
    }
    chaser.roll();
    frameIndex++;
}

// void MarqueeAnimation::drawFrame() {
    // uint16_t row = 0;
    // for (std::vector<uint16_t> path : paths) {
    //     uint16_t chaserIndex = 0;
    //     for (uint16_t pixelIndex : path) {
    //         uint32_t color = chaser.get(chaserIndex++);
    //         bool black = 0 == ((chaserIndex + frameIndex) % 3);
    //         display.setPixel(pixelIndex, black ? 0 : color);
    //     }
    // }
    // display.update();
    // chaser.roll();
    // frameIndex++;
// }

std::vector<std::vector<uint16_t>> MarqueeAnimation::paths = {
        { 0, 1, 2, 3, 4, 5, 6, 7 },
        { 8, 9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23 },
        { 24, 25, 26, 27, 28, 29, 30, 31,},
        { 32, 33, 34, 35, 36, 37, 38, 39 },
        { 40, 41, 42, 43, 44, 45, 46, 47 },
        { 48, 49, 50, 51, 52, 53, 54, 55 },
        { 56, 57, 58, 59, 60, 61, 62, 63 }
};
