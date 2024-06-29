#pragma once

#include "Animation.h"
#include "Chaser.h"
#include <vector>

// helper class combines chaser and path
class ChaserPath {
public:
    Chaser *chaser;
    std::vector<uint16_t> path;
    ChaserPath(Chaser *chaser, std::vector<uint16_t> path) {
        this->chaser = chaser;
        this->path = path;
    }
};

// the animation class
class PathAnimation : public Animation {
public:
    PathAnimation();
    PathAnimation(uint16_t framePeriodMilis);
    virtual ~PathAnimation() {}

    virtual void drawFrame(Frame &frame) override;
    void reverse();
protected:
    std::vector<ChaserPath> chaserPaths;
    void drawPath(std::vector<uint16_t> spiral, Chaser *chaser);
};

