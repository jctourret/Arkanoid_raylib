#include "Ball.h"
Ball ball;
const int ballPosition = GetScreenWidth() / 2;
void BallF::init(Ball ball, int XY){
	ball.Position.x = XY;
	ball.Position.y = XY;
}