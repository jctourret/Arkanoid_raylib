#ifndef BALL_H
#define BALL_H
#include "raylib.h"
struct Ball {
	Vector2  Position;
	int Radius;
	Color color;
	Vector2 Speed;
};
extern Ball ball;
extern const int ballPosition = GetScreenWidth() / 2;
namespace BallF {
	extern void init(Ball ball, int XY);
}
#endif BALL_H