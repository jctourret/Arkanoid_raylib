#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Bricks
{
	Vector2 position;
	bool active;
};
const int bricksPerLine = 20;
const int linesOfBricks = 5;
Bricks brick[linesOfBricks][bricksPerLine];

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	bool gameMenuOn = true;
	Vector2 ballMenuPosition;
	Vector2 ballPosition;
	ballPosition.x = screenWidth / 2;
	ballPosition.y = screenHeight / 2;
	Vector2 ballSpeed = { 4,3 };
	Rectangle rectMenu;
	rectMenu.width = 100;
	rectMenu.height = 50;
	rectMenu.x = 350;
	rectMenu.y = 250;
	Rectangle rectMenu2;
	rectMenu2.width = 100;
	rectMenu2.height = 50;
	rectMenu2.x = 350;
	rectMenu2.y = 350;
	Rectangle player;
	player.width = 75;
	player.height = 10;
	player.x = screenWidth / 2;
	player.y = screenHeight-screenHeight / 10;
	Rectangle Brick;
	Brick.width = screenWidth/bricksPerLine;
	Brick.height = 40;
	int ballRadius = 10;
	int blockCollums = 5;
	int blockRows = 10;
	int playerSpeed = 8;
	int playerlives = 5;
	bool Victory=false;
	bool gameOver = false;
	bool ballActive = true;
	SetTargetFPS(60);
	do {
		while (gameMenuOn && !WindowShouldClose()){
			ballMenuPosition = GetMousePosition();

			bool menuCollision = CheckCollisionCircleRec(ballMenuPosition, ballRadius, rectMenu);
			bool menuCollision2 = CheckCollisionCircleRec(ballMenuPosition, ballRadius, rectMenu2);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && menuCollision) {
				gameMenuOn = false;
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && menuCollision2) {
				return 0;
			}
			BeginDrawing();
			ClearBackground(BLACK);
			DrawRectangleRec(rectMenu, RED);
			DrawRectangleRec(rectMenu2, RED);
			DrawText("ARKAN0ID", rectMenu.x -50, rectMenu.y - 200, 40, RAYWHITE);
			DrawText("Play", rectMenu.x + 30, rectMenu.y + 15, 20, RAYWHITE);
			DrawText("Exit", rectMenu2.x + 30, rectMenu2.y + 15, 20, RAYWHITE);
			EndDrawing();
		}
		int initialDownPosition = 50;
		for (int i = 0; i < linesOfBricks; i++){
			for (int j = 0; j < bricksPerLine; j++){
				brick[i][j].position = { j*Brick.width + Brick.width / 2, i*Brick.height + initialDownPosition };
				brick[i][j].active = true;
			}
		}
		while (!gameOver && !WindowShouldClose()){
			if (IsKeyDown(KEY_D))player.x += playerSpeed;
			if (IsKeyDown(KEY_A))player.x -= playerSpeed;
			if (IsKeyDown(KEY_RIGHT))player.x += playerSpeed;
			if (IsKeyDown(KEY_LEFT))player.x -= playerSpeed;
			if (player.x<0) player.x=0;
			if ((player.x + player.width) >= screenWidth) player.x = screenWidth - player.width;
			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;
			if (!ballActive){
				if (IsKeyPressed(KEY_SPACE))
				{
					ballActive=true;
					ballSpeed={0,-5};
				}
			}
			if (ballActive){
				ballPosition.x += ballSpeed.x;
				ballPosition.y += ballSpeed.y;
			}
			else{
				ballPosition={player.x+player.width/2, player.y-25};
			}
			if (ballPosition.y>=(GetScreenHeight()-ballRadius))ballSpeed.y = -ballSpeed.y;
			if (((ballPosition.x + ballRadius) >= screenWidth) || ((ballPosition.x - ballRadius) <= 0)) ballSpeed.x *= -1;
			if ((ballPosition.y - ballRadius) <= 0) ballSpeed.y *= -1;
			if ((ballPosition.y + ballRadius) >= screenHeight){
				ballSpeed={ 0, 0 };
				playerlives--;
				ballActive = false;
			}
			if (CheckCollisionCircleRec(ballPosition, ballRadius,player)){
				if (ballSpeed.y > 0){
					ballSpeed.y *= -1;
					ballSpeed.x = (ballPosition.x - player.x) / (player.width / 2) * 5;
				}
			}
			for (int i = 0; i < linesOfBricks; i++){
				for (int j = 0; j < bricksPerLine; j++){
					if (brick[i][j].active){
						// Hit below
						if (((ballPosition.y - ballRadius) <= (brick[i][j].position.y + Brick.height)) &&
							((ballPosition.y - ballRadius) > (brick[i][j].position.y + Brick.height + ballSpeed.y)) &&
							((fabs(ballPosition.x - brick[i][j].position.x)) < (Brick.width+ ballRadius / 3)) && (ballSpeed.y < 0)){
							brick[i][j].active = false;
							ballSpeed.y *= -1;
						}
						// Hit above
						else if (((ballPosition.y + ballRadius) >= (brick[i][j].position.y - Brick.height)) &&
							((ballPosition.y + ballRadius) < (brick[i][j].position.y - Brick.height+ ballSpeed.y)) &&
							((fabs(ballPosition.x - brick[i][j].position.x)) < (Brick.width + ballRadius / 3)) && (ballSpeed.y > 0)){
							brick[i][j].active = false;
							ballSpeed.y *= -1;
							}
						// Hit left
						else if (((ballPosition.x + ballRadius) >= (brick[i][j].position.x - Brick.width)) &&
							((ballPosition.x + ballRadius) < (brick[i][j].position.x - Brick.width+ ballSpeed.x)) &&
							((fabs(ballPosition.y - brick[i][j].position.y))<(Brick.height+ ballRadius / 3)) && (ballSpeed.x > 0)){
							brick[i][j].active = false;
							ballSpeed.x *= -1;
							}
						// Hit right
						else if (((ballPosition.x - ballRadius) <= (brick[i][j].position.x + Brick.width)) &&
							((ballPosition.x - ballRadius) > (brick[i][j].position.x + Brick.width+ ballSpeed.x)) &&
							((fabs(ballPosition.y - brick[i][j].position.y)) < (Brick.height+ ballRadius / 3)) && (ballSpeed.x < 0)){
							brick[i][j].active = false;
							ballSpeed.x *= -1;
							}
					}
				}
			}
			if (playerlives <= 0)
			{
				gameOver = true;
			}
			BeginDrawing();
			ClearBackground(BLACK);
			DrawRectangle(player.x, player.y, player.width, player.height, GRAY);
			DrawCircleV(ballPosition, ballRadius, MAROON);
			for (int i = 0; i < linesOfBricks; i++)
			{
				for (int j = 0; j < bricksPerLine; j++)
				{
					if (brick[i][j].active)
					{
						if ((i + j) % 2 == 0) DrawRectangle(brick[i][j].position.x - Brick.width / 2, brick[i][j].position.y - Brick.height / 2, Brick.width, Brick.height, GRAY);
						else DrawRectangle(brick[i][j].position.x - Brick.width / 2, brick[i][j].position.y - Brick.height / 2, Brick.width, Brick.height, DARKGRAY);
					}
				}
			}
			EndDrawing();
		}
		while (gameOver && !WindowShouldClose()){
			ballMenuPosition = GetMousePosition();

			bool menuCollision = CheckCollisionCircleRec(ballMenuPosition, ballRadius, rectMenu);
			bool menuCollision2 = CheckCollisionCircleRec(ballMenuPosition, ballRadius, rectMenu2);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && menuCollision) {
				gameOver = false;
				gameMenuOn = true;
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && menuCollision2) {
				return 0;
			}
			for (int i = 0; i < linesOfBricks; i++){
				for (int j = 0; j < bricksPerLine; j++){
					if (brick[i][j].active=false) Victory = true;
				}
			}
			if (Victory){
				BeginDrawing();
				ClearBackground(BLACK);
				DrawText("You WIN!", rectMenu.x - 50, rectMenu.y - 200, 40, RAYWHITE);
			}
			else {
				BeginDrawing();
				ClearBackground(BLACK);
				DrawText("You LOSE!", rectMenu.x - 50, rectMenu.y - 200, 40, RAYWHITE);
			}
			DrawRectangleRec(rectMenu, RED);
			DrawRectangleRec(rectMenu2, RED);
			DrawText("Play", rectMenu.x + 30, rectMenu.y + 15, 20, RAYWHITE);
			DrawText("Menu", rectMenu2.x + 30, rectMenu2.y + 15, 20, RAYWHITE);
			EndDrawing();
		}
	} while (!gameOver && !WindowShouldClose());
	CloseWindow();
	return 0;
}