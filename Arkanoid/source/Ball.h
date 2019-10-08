#ifndef BALL_H
#define BALL_H
#include "raylib.h"
namespace balls {
	struct Ball {
		Vector2  Position;
		int Radius;
		Color color;
		Vector2 Speed;
	};
	extern Ball ball;
	extern const int ballPosition;
	extern void init(Ball ball, int XY);
}
#endif BALL_H