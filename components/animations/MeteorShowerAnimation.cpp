#include "MeteorShowerAnimation.h"

MeteorShowerAnimation::MeteorShowerAnimation(Display &display) : PathAnimation(display) {
    chaserPaths = {
        ChaserPath(new CandyChaser(16), { 0 }),
        ChaserPath(new CandyChaser(16), { 8, 1 }),
        ChaserPath(new CandyChaser(16), { 16, 9, 2 }),
        ChaserPath(new CandyChaser(16), { 24, 17, 10, 3 }),
        ChaserPath(new CandyChaser(16), { 32, 25, 18, 11, 4 }),
        ChaserPath(new CandyChaser(16), { 40, 33, 26, 19, 12, 5 }),
        ChaserPath(new CandyChaser(16), { 48, 41, 34, 27, 20, 13, 6 }),
        ChaserPath(new CandyChaser(16), { 56, 49, 42, 35, 28, 21, 14, 7 }),
        ChaserPath(new CandyChaser(16), { 57, 50, 43, 36, 29, 22, 15 }),
        ChaserPath(new CandyChaser(16), { 58, 51, 44, 37, 30, 23 }),
        ChaserPath(new CandyChaser(16), { 59, 52, 45, 38, 31 }),
        ChaserPath(new CandyChaser(16), { 60, 53, 46, 39 }),
        ChaserPath(new CandyChaser(16), { 61, 54, 47 }),
        ChaserPath(new CandyChaser(16), { 62, 55 }),
        ChaserPath(new CandyChaser(16), { 63 })
    };
}
