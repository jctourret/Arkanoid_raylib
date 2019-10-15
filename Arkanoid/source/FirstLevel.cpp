#include "FirstLevel.h"
#include "Player.h"
#include "Bricks.h"
#include "Ball.h"
#include "Window.h"
#include "GameManager.h"
using namespace players;
using namespace gameManager;
using namespace window;
using namespace bricks;
using namespace balls;
namespace firstlv {
	const int bricksPerLine=15;
	const int linesOfBricks=5;
	bool hasCollided = false;
	float ballSpeedY = screenHeight;
	float ballSpeedXSmallIncrease = (screenWidth/8);
	float ballSpeedXBigIncrease = (screenWidth/4);
	float ballSpeedYIncrease = (screenHeight / 8);
	void input();
	void update();
	void draw();
	void drawBall(Ball ball);
	void drawPlayer(Player player);
	void movePlayer(Player &player);
	void ballBouncesPlayer(Player player, Ball &ball);
	void moveBall(Ball &ball);
	void launchBall(Ball &ball,Player player);
	void drawFirstLevel();
	void drawLivesLeft(Player player);
	void checkWin(Player player, Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Gamestates &gamestate);
	void initFirstLevel(Brick (&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick);
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick, Ball &ball);
	Brick bricksOfLevel[linesOfBricks][bricksPerLine];
	extern bool initOnce = true;
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
		ballBouncesPlayer(player, ball);
		breakBricks(bricksOfLevel, brick, ball);
		checkWin(player, bricksOfLevel, Gamestate);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawBall(ball);
		drawLivesLeft(player);
		drawFirstLevel();
		EndDrawing();
	}
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine],Brick individualBrick, Ball &ball) {
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brickMatrix[i][j].active){
					//Hit Up
					if (ball.Position.y + ball.Radius >= brickMatrix[i][j].Body.y &&
						ball.Position.y + ball.Radius < brickMatrix[i][j].Body.y+brickMatrix[i][j].Body.height &&
						ball.Position.x > brickMatrix[i][j].Body.x &&
						ball.Position.x < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width) {
						brickMatrix[i][j].active = false;
						ball.SpeedY *= -1;
					}
					//Hit Down 
					if (ball.Position.y - ball.Radius <= brickMatrix[i][j].Body.y+brickMatrix[i][j].Body.height &&
						ball.Position.y - ball.Radius > brickMatrix[i][j].Body.y &&
						ball.Position.x > brickMatrix[i][j].Body.x &&
						ball.Position.x < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width) {
						brickMatrix[i][j].active = false;
						ball.SpeedY *= -1;
					}
					//Hit Right
					if (ball.Position.x - ball.Radius <= brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width &&
						ball.Position.x - ball.Radius > brickMatrix[i][j].Body.x &&
						ball.Position.y > brickMatrix[i][j].Body.y &&
						ball.Position.y < brickMatrix[i][j].Body.y + brickMatrix[i][j].Body.height) {
						brickMatrix[i][j].active = false;
						ball.SpeedX *= -1;
					}
					//Hit Left
					if (ball.Position.x + ball.Radius >= brickMatrix[i][j].Body.x &&
						ball.Position.x + ball.Radius < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width &&
						ball.Position.y > brickMatrix[i][j].Body.y &&
						ball.Position.y < brickMatrix[i][j].Body.y + brickMatrix[i][j].Body.height) {
						brickMatrix[i][j].active = false;
						ball.SpeedX *= -1;
					}
				}
			}
		}
	}
	void movePlayer(Player &player) {
		float time = GetFrameTime();
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed*time;
		if ((player.Body.x) <= 0) player.Body.x = 1;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed*time;
		if ((player.Body.x + player.Body.width) >= screenWidth) player.Body.x = screenWidth - player.Body.width;
	}
	bool ballHittingPlayer(Ball ball, Player player) {
		if (CheckCollisionCircleRec(ball.Position, ball.Radius, player.Body)) {
			return true;
		}
		else {
			return false;
		}
	}
	void ballBouncesPlayer(Player player, Ball &ball) {
		ballHittingPlayer(ball, player);
		if (hasCollided == false && ballHittingPlayer(ball, player)) {
			if (player.Body.x + player.Body.width / 4 >= ball.Position.x) {
				if (ball.SpeedX > 0) { ball.SpeedX = (-ball.SpeedX) - ballSpeedXBigIncrease; }
				if (ball.SpeedX <= 0) { ball.SpeedX -= ballSpeedXBigIncrease; }
			}
			if (player.Body.x + player.Body.width / 2 >= ball.Position.x&&
				player.Body.x + player.Body.width / 4 < ball.Position.x) {
				if (ball.SpeedX > 0) { ball.SpeedX = (-ball.SpeedX) - ballSpeedXSmallIncrease; } // si esta bajando que la invierta y acelere
				if (ball.SpeedX <= 0) { ball.SpeedX -= ballSpeedXSmallIncrease; } // si esta subiendo que acelere
			}
			if (player.Body.x + player.Body.width / 2 < ball.Position.x&&
				player.Body.x + player.Body.width / 2 + player.Body.width / 4 > ball.Position.y) {
				if (ball.SpeedX < 0) { ball.SpeedX = (-ball.SpeedX) + ballSpeedXSmallIncrease; } // si esta subiendo que se invierta  y acelere
				if (ball.SpeedX >= 0) { ball.SpeedX += ballSpeedXSmallIncrease; } // si esta bajando acelera
			}
			if (player.Body.y + player.Body.height / 2 + player.Body.height / 4 <= ball.Position.y) {
				if (ball.SpeedX < 0) { ball.SpeedX = (-ball.SpeedX) + ballSpeedXBigIncrease; }
				if (ball.SpeedX >= 0) { ball.SpeedX += ballSpeedXBigIncrease; }
			}
			if (ball.SpeedY > 0)
			{
				ball.SpeedY++;
			}
			if (ball.SpeedY < 0)
			{
				ball.SpeedY--;
			}
			ball.SpeedY = -ball.SpeedY;
			hasCollided = true;
			ball.color = player.Color;
		}
		if (!(ballHittingPlayer(ball, player))) {
			hasCollided = false;
		}
	}
	void drawLivesLeft(Player player) {
		for (int i = 0; i <player.Lives; i++) {
			DrawRectangle((i*player.Body.width), screenHeight - (player.Body.height * 2), player.Body.width / 2, player.Body.height / 2, player.Color);
		}
	}
	void moveBall(Ball &ball) {
		float time = GetFrameTime();
		ball.Position.x += (ball.SpeedX*time);
		if (ball.Position.x + ball.Radius >= screenWidth) { ball.SpeedX *= -1; }
		if (ball.Position.x - ball.Radius <= 0) {
			ball.Position.x = ball.Position.x + ball.Radius;
			ball.SpeedX *= -1;
		}
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
				ball.SpeedX = 0;
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
	void checkWin(Player player, Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Gamestates &gamestate) {
		int bricksBroken = 0;
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brickMatrix[i][j].active == false) {
					bricksBroken++;
				}
			}
		}
		if (bricksBroken==(linesOfBricks*bricksPerLine) || player.Lives==0){
			gamestate = End;
		}
	}
}