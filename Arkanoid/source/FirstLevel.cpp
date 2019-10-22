#include "Player.h"
#include "PowerUp.h"
#include "Ball.h"
#include "Bricks.h"
#include "Window.h"
#include "GameManager.h"
using namespace players;
using namespace powerup;
using namespace balls;
using namespace bricks;
using namespace window;
using namespace gameManager;
namespace firstlv {

	const int bricksPerLine=10;
	const int linesOfBricks=3;
	int averageBrickLives = 1;
	int strongBrickLives = 2;
	int powerFallSpeed = screenHeight / 16;
	int bulletSpeed = screenHeight / 12;
	bool hasCollided = false;
	bool gunIsOn = false;
	bool catchIsOn = false;
	extern bool initOnce = true;
	float ballSpeedY = screenHeight;
	float ballSpeedXSmallIncrease = (screenWidth/8);
	float ballSpeedXBigIncrease = (screenWidth/4);
	float ballSpeedYIncrease = (screenHeight / 8);
	float widthBetweenBricks = screenWidth / 33;
	float heigthBetweenBricks = screenHeight / 20;
	Brick bricksOfLevel[linesOfBricks][bricksPerLine];
	
	void initFirstLevel(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick);
	void input();
	void update();
	void draw();
	void drawBall(Ball ball);
	void drawPlayer(Player player);
	void drawBricks();
	void drawPlayerLives(Player player);
	void drawPowerUp(PowerUp power);
	void movePlayer(Player &player);
	void moveBall(Ball &ball);
	void launchBall(Ball &ball,Player player);
	void ballBouncesPlayer(Player player, Ball &ball);
	void randomPowerUp();
	void spawnPowerUp(PowerUp &power, Brick(&brickMatrix)[linesOfBricks][bricksPerLine]);
	void dropPowerUp(PowerUp &power);
	void triggerGun(Player player, Brick(&brickMatrix)[linesOfBricks][bricksPerLine]);
	void triggerGrowPlayer(Player &player);
	void triggerCatch(Player player);
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick, Ball &ball);
	void checkWin(Player player, Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Gamestates &gamestate);
	bool ballHittingPlayer(Ball ball, Player player);

	void run() {
		if (initOnce){
			initFirstLevel(bricksOfLevel,brick);
			initOnce = false;
		}
		input();
		update();
		draw();
	}
	void initFirstLevel(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick) {
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				brickMatrix[i][j].Body.x = widthBetweenBricks + (j* widthBetweenBricks + j * individualBrick.Body.width);
				brickMatrix[i][j].Body.y = heigthBetweenBricks + (i*heigthBetweenBricks + i * individualBrick.Body.height);
				brickMatrix[i][j].Body.width = individualBrick.Body.width;
				brickMatrix[i][j].Body.height = individualBrick.Body.height;
				brickMatrix[i][j].Active = true;
				int random = GetRandomValue(0, 10);
				if (random <= 3) {
					brickMatrix[i][j].Color = BLUE;
					brickMatrix[i][j].Lives = averageBrickLives;
					brickMatrix[i][j].Powerup = false;
				}
				else if (random > 3 && random <= 6) {
					brickMatrix[i][j].Color = RED;
					brickMatrix[i][j].Lives = averageBrickLives;
					brickMatrix[i][j].Powerup = false;
				}
				else if (random >6 && random <=9 ) {
					brickMatrix[i][j].Color = YELLOW;
					brickMatrix[i][j].Lives = averageBrickLives;
					brickMatrix[i][j].Powerup = false;
				}
				else if (random == 10) {
					brickMatrix[i][j].Color = GRAY;
					brickMatrix[i][j].Lives = strongBrickLives;
					brickMatrix[i][j].Powerup = true;
				}
			}
		}
	}
	void input() {
		movePlayer(player);
		launchBall(ball,player);
	}
	void update() {
		moveBall(ball);
		ballBouncesPlayer(player, ball);
		breakBricks(bricksOfLevel, brick, ball);
		randomPowerUp();
		dropPowerUp(CatchBall);
		dropPowerUp(GrowPlayer);
		dropPowerUp(Gun);
		checkWin(player, bricksOfLevel, Gamestate);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawBall(ball);
		drawPlayerLives(player);
		drawPowerUp(GrowPlayer);
		drawPowerUp(CatchBall);
		if (gunIsOn){
			DrawRectangleRec(Gun.Body, Gun.Color);
			DrawRectangleRec(Gun.Bullet, Gun.Color);}
		drawBricks();
		EndDrawing();
	}
	void drawBall(Ball ball) {
		DrawCircle(ball.Position.x, ball.Position.y, ball.Radius, ball.color);
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	void drawBricks(){
		for (int i = 0; i < linesOfBricks; i++) {
			for (int j = 0; j < bricksPerLine; j++) {
				if (bricksOfLevel[i][j].Active == true) {
					DrawRectangleRec(bricksOfLevel[i][j].Body, bricksOfLevel[i][j].Color);
				}
			}
		}
	}
	void drawPlayerLives(Player player) {
		for (int i = 0; i < player.Lives; i++) {
			DrawRectangle((i*player.Body.width), screenHeight - (player.Body.height * 2), player.Body.width / 2, player.Body.height / 2, player.Color);
		}
	}
	void movePlayer(Player &player) {
		float time = GetFrameTime();
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed*time;
		if ((player.Body.x) <= 0) player.Body.x = 1;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed*time;
		if ((player.Body.x + player.Body.width) >= screenWidth) player.Body.x = screenWidth - player.Body.width;
	}
	void moveBall(Ball &ball) {
		float time = GetFrameTime();
		ball.Position.x += (ball.SpeedX*time);
		if (ball.Position.x + ball.Radius >= screenWidth) {
			ball.Position.x = ball.Position.x - ball.Radius;
			ball.SpeedX *= -1; 
		}
		if (ball.Position.x - ball.Radius <= 0) {
			ball.Position.x = ball.Position.x + ball.Radius;
			ball.SpeedX *= -1;
		}
		ball.Position.y += (ball.SpeedY*time);
		if (ball.Position.y - ball.Radius <= 0) {
			ball.Position.y = ball.Position.y + ball.Radius;
			ball.SpeedY *= -1;
		}
		if (ball.Position.y + ball.Radius >= screenHeight) {
			ball.Active = false;
			player.Lives--;
		}
	}
	void launchBall(Ball &ball, Player player) {
		if (!ball.Active)
		{
			ball.Position.y = player.Body.y - 20;
			ball.Position.x = player.Body.x + (player.Body.width / 2);
			if (IsKeyPressed(KEY_SPACE))
			{
				ball.Active = true;
				ball.SpeedX = 0;
				ball.SpeedY = (-1 * ballSpeedY);
			}
		}
	}
	void ballBouncesPlayer(Player player, Ball &ball) {
		ballHittingPlayer(ball, player);
		if (hasCollided == false && ballHittingPlayer(ball, player)) {
			if (player.Body.x + player.Body.width / 4 >= ball.Position.x) {
				if (ball.SpeedX > 0) { ball.SpeedX = (-ball.SpeedX) - ballSpeedXBigIncrease; }
				else if (ball.SpeedX <= 0) { ball.SpeedX -= ballSpeedXBigIncrease; }
			}
			if (player.Body.x + player.Body.width / 2 > ball.Position.x&&
				player.Body.x + player.Body.width / 4 < ball.Position.x) {
				if (ball.SpeedX > 0) { ball.SpeedX = (-ball.SpeedX) - ballSpeedXSmallIncrease; }
				else if (ball.SpeedX <= 0) { ball.SpeedX -= ballSpeedXSmallIncrease; }
			}
			if (player.Body.x + player.Body.width / 2 < ball.Position.x&&
				player.Body.x + player.Body.width / 2 + player.Body.width / 4 > ball.Position.x) {
				if (ball.SpeedX < 0) { ball.SpeedX = (-ball.SpeedX) + ballSpeedXSmallIncrease; }
				else if (ball.SpeedX >= 0) { ball.SpeedX += ballSpeedXSmallIncrease; }
			}
			if (player.Body.x + player.Body.width / 2 + player.Body.width / 4 <= ball.Position.x) {
				if (ball.SpeedX < 0) { ball.SpeedX = (-ball.SpeedX) + ballSpeedXBigIncrease; }
				else if (ball.SpeedX >= 0) { ball.SpeedX += ballSpeedXBigIncrease; }
			}
			ball.SpeedY++;
			ball.SpeedY = -ball.SpeedY;
			hasCollided = true;
		}
		if (!(ballHittingPlayer(ball, player))) {
			hasCollided = false;
		}
	}
	void breakBricks(Brick(&brickMatrix)[linesOfBricks][bricksPerLine],Brick individualBrick, Ball &ball) {
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brickMatrix[i][j].Active){
					if (ball.Position.y + ball.Radius >= brickMatrix[i][j].Body.y &&
						ball.Position.y + ball.Radius < brickMatrix[i][j].Body.y+brickMatrix[i][j].Body.height &&
						ball.Position.x > brickMatrix[i][j].Body.x &&
						ball.Position.x < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width) {
						brickMatrix[i][j].Lives--;
						if (brickMatrix[i][j].Lives == 0) {
							brickMatrix[i][j].Active = false;
						}
						ball.SpeedY *= -1;
					}
					if (ball.Position.y - ball.Radius <= brickMatrix[i][j].Body.y+brickMatrix[i][j].Body.height &&
						ball.Position.y - ball.Radius > brickMatrix[i][j].Body.y &&
						ball.Position.x > brickMatrix[i][j].Body.x &&
						ball.Position.x < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width) {
						brickMatrix[i][j].Lives--;
						if (brickMatrix[i][j].Lives == 0) {
							brickMatrix[i][j].Active = false;
						}
						ball.SpeedY *= -1;
					}
					if (ball.Position.x - ball.Radius <= brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width &&
						ball.Position.x - ball.Radius > brickMatrix[i][j].Body.x &&
						ball.Position.y > brickMatrix[i][j].Body.y &&
						ball.Position.y < brickMatrix[i][j].Body.y + brickMatrix[i][j].Body.height) {
						brickMatrix[i][j].Lives--;
						if (brickMatrix[i][j].Lives == 0) {
							brickMatrix[i][j].Active = false;
						}
						ball.SpeedX *= -1;
						if (ball.SpeedX == 0) { ball.SpeedX -= ballSpeedXSmallIncrease; }
					}
					if (ball.Position.x + ball.Radius >= brickMatrix[i][j].Body.x &&
						ball.Position.x + ball.Radius < brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width &&
						ball.Position.y > brickMatrix[i][j].Body.y &&
						ball.Position.y < brickMatrix[i][j].Body.y + brickMatrix[i][j].Body.height) {
						brickMatrix[i][j].Lives--;
						if (brickMatrix[i][j].Lives == 0) {
							brickMatrix[i][j].Active = false;
						}
						ball.SpeedX *= -1;
						if (ball.SpeedX == 0) { ball.SpeedX -= ballSpeedXSmallIncrease; }
					}
				}
			}
		}
	}
	void checkWin(Player player, Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Gamestates &gamestate) {
		int bricksBroken = 0;
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brickMatrix[i][j].Active == false) {
					bricksBroken++;
				}
			}
		}
		if (bricksBroken==(linesOfBricks*bricksPerLine) || player.Lives==0){
			gamestate = End;
		}
	}
	bool ballHittingPlayer(Ball ball, Player player) {
		if (CheckCollisionCircleRec(ball.Position, ball.Radius, player.Body)) {
			return true;
		}
		else {
			return false;
		}
	}
	void randomPowerUp() {
		int random = GetRandomValue(0,2);
		switch (random)
		{
		case 0:
			GrowPlayer.Color = GREEN;
			spawnPowerUp(GrowPlayer, bricksOfLevel);
			break;
		case 1:
			Gun.Color = RED;
			spawnPowerUp(Gun, bricksOfLevel);
			break;
		case 2:
			CatchBall.Color = YELLOW;
			spawnPowerUp(CatchBall, bricksOfLevel);
			break;
		}
	}
	void spawnPowerUp(PowerUp &power, Brick(&brickMatrix)[linesOfBricks][bricksPerLine]) {
		for (int i = 0; i < linesOfBricks; i++) {
			for (int j = 0; j < bricksPerLine; j++) {
				if (brickMatrix[i][j].Active == false && brickMatrix[i][j].Powerup == true) {
					power.Body.y = brickMatrix[i][j].Body.y;
					power.Body.x = brickMatrix[i][j].Body.x + brickMatrix[i][j].Body.width;
					power.Active = true;
					brickMatrix[i][j].Powerup = false;
				}
			}
		}
	}
	void drawPowerUp(PowerUp power) {
		if (power.Active == true) {
			DrawRectangleRec(power.Body, power.Color);
		}
	}
	void dropPowerUp(PowerUp &power) {
		if (power.Active==true) {
		int time = GetFrameTime();
		power.Body.y -= powerFallSpeed * time;
		}
	}
	void triggerGrowPlayer(Player &player) {
		int time = GetFrameTime();
		int timer;
		if (GrowPlayer.Active && CheckCollisionRecs(GrowPlayer.Body,player.Body)) {
			GrowPlayer.Active = false;
			player.Body.width += 10;
		}
		timer += 1 * time;
		if (timer > 30) {
			timer = 0;
			player.Body.width -= 10;
		}
	}
	void triggerGun(Player player,Brick(&brickMatrix)[linesOfBricks][bricksPerLine]) {
		int time = GetFrameTime();
		int timer;
		if (CheckCollisionRecs(Gun.Body, player.Body)) {
			Gun.Active = false;
			gunIsOn;
		}
		while (gunIsOn) {
			Gun.Body.x = player.Body.x + (player.Body.width / 2);
			Gun.Body.y = player.Body.y;
			if (IsKeyDown(KEY_SPACE)) {
				Gun.BulletActive = true;
			}
			if (!Gun.BulletActive) {
				Gun.Bullet.x = Gun.Body.x;
				Gun.Bullet.y = Gun.Body.y;
			}
			if (Gun.BulletActive) {
				Gun.Bullet.y += bulletSpeed * time;
				for (int i = 0; i < linesOfBricks; i++) {
					for (int j = 0; j < bricksPerLine; j++) {
						if (CheckCollisionRecs(brickMatrix[i][j].Body, Gun.Bullet)) {
							brickMatrix[i][j].Lives--;
							if (brickMatrix[i][j].Lives == 0) {
								brickMatrix[i][j].Active = false;
							}
							Gun.BulletActive = false;
						}
					}
				}
			}
			timer += 1 * time;
			if (timer > 30) {
				timer = 0;
				gunIsOn = false;
			}
		}
	}
	void triggerCatch(Player player) {
		int time = GetFrameTime();
		int timer;
		if (CheckCollisionRecs(Gun.Body, player.Body)) {
			CatchBall.Active = false;
		}
		if (catchIsOn){
			if (ballHittingPlayer(ball,player)){
				ball.Active=false;
			}
			timer += 1 * time;
			if (timer > 30) {
				timer = 0;
				catchIsOn = false;
			}
		}
	}
}