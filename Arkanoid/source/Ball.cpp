#include "Ball.h"
namespace balls {
	Ball ball;
	const int ballPosition = GetScreenWidth() / 2;
	void init(Ball ball, int XY) {
		ball.Position.x = XY;
		ball.Position.y = XY;
	}
}