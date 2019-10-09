#include "Ball.h"
namespace balls{
	struct Ball {
		Vector2  Position;
		int Radius;
		Color color;
		Vector2 Speed;
	};
	Ball ball;
	const int ballPosition = GetScreenWidth() / 2;
	void initBall(Ball ball, int XY);
	void init(){
		initBall(ball, ballPosition);
	}
	void initBall(Ball ball, int XY){
		ball.Position.x = XY;
		ball.Position.y = XY;
	}
}