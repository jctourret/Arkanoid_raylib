#include "FirstLevel.h"
#include "Player.h"
#include "Bricks.h"
#include "Ball.h"
#include "Window.h"
using namespace players;
using namespace window;
using namespace bricks;
using namespace balls;
namespace firstlv {
	const int bricksPerLine=15;
	const int linesOfBricks=5;
	bool brickBroken = false;
	float ballSpeedX = (screenWidth);
	float ballSpeedY = (screenHeight);
	void input();
	void update();
	void draw();
	void drawBall(Ball ball);
	void drawPlayer(Player player);
	void movePlayer(Player &player);
	void moveBall(Ball &ball);
	void launchBall(Ball &ball,Player player);
	void drawFirstLevel();
	void initFirstLevel(Brick (&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick);
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick, Ball &ball);
	Brick bricksOfLevel[linesOfBricks][bricksPerLine];
	bool initOnce = true;
	void run() {
		if (initOnce){
			initFirstLevel(bricksOfLevel,brick);
			initOnce = false;
		}
		input();
		update();
		draw();
	}
	void input() {
		movePlayer(player);
		launchBall(ball,player);
	}
	void update() {
		moveBall(ball);
		breakBricks(bricksOfLevel, brick, ball);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawBall(ball);
		drawFirstLevel();
		EndDrawing();
	}
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine],Brick individualBrick, Ball &ball) {
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brickMatrix[i][j].active){
					if (CheckCollisionCircleRec(ball.Position, ball.Radius, brickMatrix[i][j].Body&&
						ball.Position.x+ ball.Radius =)) {
						ball.Active = false;
						player.Lives--;
					}
				}
			}
		}
	}
	void movePlayer(Player &player) {
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed;
		if ((player.Body.x) <= 0) player.Body.x = 1;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed;
		if ((player.Body.x + player.Body.width) >= screenWidth) player.Body.x = screenWidth - player.Body.width;
	}
	void moveBall(Ball &ball) {
		float time = GetFrameTime();
		ball.Position.x += (ball.SpeedX*time);
		if (ball.Position.x + ball.Radius >= screenWidth) { ball.SpeedX *= -1; }
		if (ball.Position.x - ball.Radius <= 0) { ball.SpeedX *= -1; }
		ball.Position.y += (ball.SpeedY*time);
		if (ball.Position.y - ball.Radius <= 0) { ball.SpeedY *= -1; }
		if (ball.Position.y + ball.Radius >= screenHeight) {
			ball.Active = false;
			player.Lives--;
		}
	}
	void launchBall(Ball &ball,Player player) {
		if (!ball.Active)
		{
			ball.Position.y = player.Body.y-20;
			ball.Position.x = player.Body.x + (player.Body.width / 2);
			if (IsKeyPressed(KEY_SPACE))
			{
				ball.Active = true;
				ball.SpeedX = (-1 * ballSpeedX);
				ball.SpeedY = (-1 * ballSpeedY);
			}
		}
	}
	void drawBall(Ball ball) {
		DrawCircle(ball.Position.x, ball.Position.y, ball.Radius, ball.color);
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	void initFirstLevel(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick) {
		for (int i = 0; i < linesOfBricks; i++)
		{
			for (int j = 0; j < bricksPerLine; j++)
			{
				brickMatrix[i][j].Body.x= j* individualBrick.Body.width;
				brickMatrix[i][j].Body.y = i * individualBrick.Body.height;
				brickMatrix[i][j].Body.width = individualBrick.Body.width;
				brickMatrix[i][j].Body.height = individualBrick.Body.height;
				brickMatrix[i][j].active = true;
			}
		}
	}
	void drawFirstLevel() {
		for (int i = 0; i < linesOfBricks; i++) {
			for (int j = 0; j < bricksPerLine; j++) {
				if (bricksOfLevel[i][j].active) {
					if ((i + j) % 2 == 0) DrawRectangleRec(bricksOfLevel[i][j].Body, GRAY);
					else DrawRectangleRec(bricksOfLevel[i][j].Body, DARKGRAY);
				}
			}
		}
	}
}