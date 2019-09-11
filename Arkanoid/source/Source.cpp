#include "raylib.h"

using namespace std;

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	bool gameMenuOn = true;
	Vector2 ballMenuPosition;
	Vector2 ballPosition;
	Vector2 ballSpeed = { 7,6 };
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
	player.x = (float)screenWidth / 20;
	player.y = (float)screenHeight / 2;
	int ballRadius = 10;
	int blockCollums = 5;
	int blockRows = 10;
	int playerSpeed = 8;
	bool gameOver = true;
	do {
		while (gameMenuOn && !WindowShouldClose())
		{
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
		while (!gameOver && !WindowShouldClose())
		{
			if (IsKeyDown(KEY_D))player.x += playerSpeed;
			if (IsKeyDown(KEY_A))player.x -= playerSpeed;
			if (IsKeyDown(KEY_RIGHT))player.y += playerSpeed;
			if (IsKeyDown(KEY_LEFT))player.y -= playerSpeed;
			if (player.x<0) player.x=0;
			if ((player.x + player.width) >= screenWidth) player.x = screenWidth - player.width;

			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;

			if (ballPosition.y>=(GetScreenHeight()-ballRadius))ballSpeed.y = -ballSpeed.y;
			if (((ballPosition.x + ballRadius) >= screenWidth) || ((ballPosition.x - ballRadius) <= 0)) ballSpeed.x *= -1;
			if ((ballPosition.y - ballRadius) <= 0) ballSpeed.y *= -1;

		}
	} while (!gameOver && !WindowShouldClose());
	CloseWindow();
	return 0;
}