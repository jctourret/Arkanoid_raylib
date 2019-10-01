#include "Ball.h"
Ball ball;
const int ballPosition = GetScreenWidth() / 2;
void BallF::initBall(){
	ball.Position.x = ballPosition;
	ball.Position.y = ballPosition;
}