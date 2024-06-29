#include "MeteorShowerAnimation.h"

MeteorShowerAnimation::MeteorShowerAnimation() {
    // NE to SW
    // matrix DIN at top left, 8x8
    // todo: make this configurable and compute the paths based on the matrix orientation
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
// SE to NW
    // chaserPaths = {
    //     ChaserPath(new CandyChaser(16), { 56 }),
    //     ChaserPath(new CandyChaser(16), { 48, 57 }),
    //     ChaserPath(new CandyChaser(16), { 40, 49, 58 }),
    //     ChaserPath(new CandyChaser(16), { 32, 41, 50, 59 }),
    //     ChaserPath(new CandyChaser(16), { 24, 33, 42, 51, 60 }),
    //     ChaserPath(new CandyChaser(16), { 16, 25, 34, 43, 52, 61 }),
    //     ChaserPath(new CandyChaser(16), { 8, 17, 26, 35, 44, 53, 62 }),
    //     ChaserPath(new CandyChaser(16), { 0, 9, 18, 27, 36, 45, 54, 63 }),
    //     ChaserPath(new CandyChaser(16), { 1, 10, 19, 28, 37, 46, 55 }),
    //     ChaserPath(new CandyChaser(16), { 2, 11, 20, 29, 38, 47 }),
    //     ChaserPath(new CandyChaser(16), { 3, 12, 21, 30, 39 }),
    //     ChaserPath(new CandyChaser(16), { 4, 13, 22, 31 }),
    //     ChaserPath(new CandyChaser(16), { 5, 14, 23 }),
    //     ChaserPath(new CandyChaser(16), { 6, 15 }),
    //     ChaserPath(new CandyChaser(16), { 7 })
    // };
}
