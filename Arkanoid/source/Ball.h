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
namespace BallF {
	extern void initBall();
}
#endif BALL_H