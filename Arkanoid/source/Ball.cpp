#include "Ball.h"
#include "Window.h"
#include "Player.h"
using namespace window;
using namespace players;
namespace balls{
	Ball ball;
	const float ballRadius = 10;
	Color ballColor = YELLOW;
	bool ballActive = false;
	
	void initBall(Ball &ball, Player player, float radius, Color color, bool active);
	
	void init(){
		initBall(ball,player, ballRadius,ballColor,ballActive);
	}
	void initBall(Ball &ball, Player player, float radius, Color color, bool active) {
		ball.Position.x = player.Body.x + (player.Body.width / 2);
		ball.Position.y = player.Body.y - 20;
		ball.Radius = radius;
		ball.SpeedX = 0;
		ball.SpeedY = 0;
		ball.color = color;
		ball.Active = active;
	}
}