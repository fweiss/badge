#pragma once

#include <map>
#include <vector>

#include "Animation.h"

class IndexedColorAnimation : public Animation {
public:
    IndexedColorAnimation() {}
    IndexedColorAnimation(uint16_t framePeriodMillis) : Animation(framePeriodMillis) {};
    virtual ~IndexedColorAnimation() {};

    virtual void drawFrame(Frame &frame) = 0;
    uint32_t frameCount = 0;
    virtual void nextFrame();

    // use this in the subclass constructor to set the frameCount from the pixelIndexes
    template<typename Index, uint32_t FrameCount>
    void setFrameCount(Index (&pixelIndexes)[FrameCount][64]) {
        frameCount = FrameCount;
    }
    template<typename Index>
    void setFrameCount2(Index (&pixelIndexes)[][64]) {
        frameCount = sizeof(pixelIndexes) / sizeof(pixelIndexes[0]);
    }

    // use this as the implementation for drawFrame(Frame&) of all derived classes
    // it will draw the frame using the colorMap and pixelIndexes
    // which are declared in terms of the derived class's ColorIndex
    // todo parameterize the pixelIndexes dimesions
    template<typename Index, uint32_t FrameCount>
    void drawFrame(Frame &frame, std::map<Index, uint32_t> &colorMap, Index (&pixelIndexes)[FrameCount][64]) {
        Index *frameIndexes = pixelIndexes[frameIndex];
        for (int i=0; i<frame.size; i++) {
            Index index = frameIndexes[i];
            uint32_t color = colorMap.at(index);
            frame.setPixel(i, color);
        }
        nextFrame();
    }
    template<typename Index>
    void drawFrame2(Frame &frame, std::map<Index, uint32_t> &colorMap, Index (&pixelIndexes)[][64]) {
        Index *frameIndexes = pixelIndexes[frameIndex];
        for (int i=0; i<frame.size; i++) {
            Index index = frameIndexes[i];
            uint32_t color = colorMap.at(index);
            frame.setPixel(i, color);
        }
        nextFrame();
    }

};
