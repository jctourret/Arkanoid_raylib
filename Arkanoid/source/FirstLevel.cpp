#include "FirstLevel.h"
#include "Player.h"
#include "Bricks.h"
#include "Ball.h"
#include "Window.h"
using namespace players;
using namespace window;
using namespace bricks;
namespace firstlv {
	const int bricksPerLine=15;
	const int linesOfBricks=5;
	int ar[5];// = { 0,1,2,3,4 };
	void input();
	void update();
	void draw();
	void drawPlayer(Player player);
	void movePlayer(Player player);
	void drawFirstLevel(Brick (&brick)[linesOfBricks][bricksPerLine]);
	void initFirstLevel(Brick (&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick);
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
	}
	void update() {

	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawPlayer(player);
		drawFirstLevel(bricksOfLevel[linesOfBricks][bricksPerLine]);
		EndDrawing();
	}
	void movePlayer(Player player) {
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed;
		if ((player.Body.x - player.Body.width) <= 0) player.Body.x = player.Body.width / 2;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed;
		if ((player.Body.x + player.Body.width) >= screenWidth) player.Body.x = screenWidth - player.Body.width;
	}
	void drawPlayer(Player player) {
		DrawRectangleRec(player.Body, player.Color);
	}
	void initFirstLevel(Brick(&brickMatrix)[linesOfBricks][bricksPerLine], Brick individualBrick) {
		for (int i = 0; i < linesOfBricks; i++)
		{
			for (int j = 0; j < bricksPerLine; j++)
			{
				brickMatrix[i][j].Body.x= j* individualBrick.Body.height;
				brickMatrix[i][j].Body.y = i * individualBrick.Body.height;
				brickMatrix[i][j].active = true;
			}
		}
	}
	void drawFirstLevel(Brick(&brick)[linesOfBricks][bricksPerLine]) {
		for (int i = 0; i < linesOfBricks; i++) {
			for (int j = 0; j < bricksPerLine; j++) {
				if (brick[i][j].active) {
					if ((i + j) % 2 == 0) DrawRectangle(brick[i][j].Body.x, brick[i][j].Body.y, brick[i][j].Body.width, brick[i][j].Body.height, GRAY);
					else DrawRectangle(brick[i][j].Body.x, brick[i][j].Body.y, brick[i][j].Body.width, brick[i][j].Body.height, DARKGRAY);
				}
			}
		}
	}
}