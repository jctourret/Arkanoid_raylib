#ifndef BALL_H
#define BALL_H
#include "raylib.h"
namespace balls {
	struct Ball {
		Vector2  Position;
		int Radius;
		Color color;
		float SpeedX;
		float SpeedY;
		bool Active;
	};
	extern Ball ball;
	extern void init();
}
#endif BALL_H