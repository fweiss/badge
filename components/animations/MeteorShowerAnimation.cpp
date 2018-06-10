#include "MeteorShowerAnimation.h"

MeteorShowerAnimation::MeteorShowerAnimation(Display &display) : PathAnimation(display) {
	chaserPaths = {
			ChaserPath(new CandyChaser(0, 20, 30), { 0 }),
			ChaserPath(new CandyChaser(10, 20, 30), { 8, 1 }),
			ChaserPath(new CandyChaser(20, 20, 30), { 16, 9, 2 }),
			ChaserPath(new CandyChaser(20, 20, 30), { 24, 17, 10, 3 }),
			ChaserPath(new CandyChaser(30, 20, 30), { 32, 25, 18, 11, 4 }),
			ChaserPath(new CandyChaser(40, 20, 30), { 40, 33, 26, 19, 12, 5 }),
			ChaserPath(new CandyChaser(50, 20, 30), { 48, 41, 34, 27, 20, 13, 6 }),
			ChaserPath(new CandyChaser(60, 20, 30), { 56, 49, 42, 35, 28, 21, 14, 7 }),
			ChaserPath(new CandyChaser(70, 20, 30), { 57, 50, 43, 36, 29, 22, 15 }),
			ChaserPath(new CandyChaser(80, 20, 30), { 58, 51, 44, 37, 30, 23 }),
			ChaserPath(new CandyChaser(90, 20, 30), { 59, 52, 45, 38, 31 }),
			ChaserPath(new CandyChaser(0, 30, 30), { 60, 53, 46, 39 }),
			ChaserPath(new CandyChaser(0, 20, 40), { 61, 54, 47 }),
			ChaserPath(new CandyChaser(0, 50, 30), { 62, 55 }),
			ChaserPath(new CandyChaser(0, 20, 70), { 63 })
	};
}
