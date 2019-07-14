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
private:
protected:
    std::vector<ChaserPath> chaserPaths;
    void drawPath(std::vector<uint16_t> spiral, Chaser *chaser);
public:
    PathAnimation(Display &display);
    void drawFrame() override;
};

