#include "scn\FirstLevel.h"
#include "obj\Window.h"
#include "sys\GameManager.h"
#include "raylib.h"
#include "obj\Player.h"
using namespace window;
using namespace players;
using namespace gameManager;
using namespace firstlv;
namespace end {
	struct Cursor {
		Vector2 Position;
		int Radius = 10;
	};
	struct Button {
		Rectangle Body;
		Color Color;
	};
	Cursor cursor;
	Button play;
	Button exit;
	const int playWidth = 100;
	const int playHeight = 50;
	const int playY = screenHeight / 2 + playHeight;
	const int playX = screenWidth / 2 - playWidth / 2;
	const int exitWidth = 100;
	const int exitHeight = 50;
	const int exitY = screenHeight / 2 + exitHeight * 3;
	const int exitX = screenWidth / 2 - exitWidth / 2;
	const Color ButtonColor = RED;
	
	void update();
	void draw();
	void initButton(Button &button, int width, int height, int x, int y, Color color);
	void drawButton(Button button);
	void drawText(Player player);
	void followMenuCursor(Cursor &cursor);
	bool buttonIsClicked(Cursor cursor, Button button);
	void exitGame(Cursor cursor, Button button);
	void startGame(Cursor cursor, Button button,gameManager::Gamestates &gamestate,Player &player);
	void run() {
		update();
		draw();
	}
	void init() {
		initButton(play, playWidth, playHeight, playX, playY, ButtonColor);
		initButton(exit, exitWidth, exitHeight, exitX, exitY, ButtonColor);
	}
	void update() {
		followMenuCursor(cursor);
		exitGame(cursor, exit);
		startGame(cursor, play, gameManager::Gamestate,player);
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawButton(play);
		drawButton(exit);
		drawText(player);
		EndDrawing();
	}
	void initButton(Button &button, int width, int height, int x, int y, Color color) {
		button.Body.width = width;
		button.Body.height = height;
		button.Body.x = x;
		button.Body.y = y;
		button.Color = color;
	}
	void followMenuCursor(Cursor &cursor) {
		cursor.Position = GetMousePosition();
	}
	void exitGame(Cursor cursor, Button button) {
		if (buttonIsClicked(cursor, button)) {
			gameManager::gameIsOn = false;
		}
	}
	void startGame(Cursor cursor, Button button, gameManager::Gamestates &gamestate, Player &player) {
		if (buttonIsClicked(cursor, button)) {
			initOnce = true;
			player.Lives = playerLives;
			gamestate = FirstLevel;
		}
	}
	void drawText(Player player) {
		DrawText("Arkanoid", GetScreenWidth() / 2 - 40, 30, 20, RAYWHITE);
		if (player.Lives == 0) {
		DrawText("YOU LOSE!", GetScreenWidth() / 2-125, GetScreenHeight() / 4, 50, RAYWHITE);
		}
		else {
		DrawText("YOU WIN!", GetScreenWidth() / 2-125, GetScreenHeight() / 4, 50, RAYWHITE);
		}
		DrawText("Play", static_cast<int>(play.Body.x) + static_cast<int>(play.Body.width) / 3, static_cast<int>(play.Body.y) + static_cast<int>(play.Body.height) / 3, 20, RAYWHITE);
		DrawText("Exit", static_cast<int>(exit.Body.x) + static_cast<int>(exit.Body.width) / 3, static_cast<int>(exit.Body.y) + static_cast<int>(exit.Body.height) / 3, 20, RAYWHITE);
	}
	void drawButton(Button button) {
		DrawRectangleRec(button.Body, button.Color);
	}
	bool buttonIsClicked(Cursor cursor, Button button) {
		if (CheckCollisionCircleRec(cursor.Position, static_cast<float>(cursor.Radius), button.Body)
			&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return true;
		}
		else {
			return false;
		}
	}
}