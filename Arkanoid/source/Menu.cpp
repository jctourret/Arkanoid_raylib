#include "Menu.h"
#include "Window.h"
using namespace gameManager;
using namespace window;
namespace menu {
	struct Cursor {
		Vector2 Position;
		Color Color = WHITE;
		Vector2 Speed = { 7.5f,6.0f };
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
	const int playY = screenHeight/2+playHeight;
	const int playX = screenWidth/2-playWidth/2;
	const int exitWidth = 100;
	const int exitHeight = 50;
	const int exitY = screenHeight/2+exitHeight*3;
	const int exitX = screenWidth/2-exitWidth/2;
	const Color ButtonColor = RED;
	bool buttonIsClicked(Cursor cursor, Button button);
	void startGame(Cursor cursor, Button button, gameManager::Gamestates &gamestate);
	void exitGame(Cursor cursor, Button button);
	void update();
	void draw();
	void drawText();
	void followMenuCursor(Cursor &cursor);
	void drawButton(Button button);
	void initButton(Button &button, int width, int height, int x, int y, Color color);
	void run() {
		update();
		draw();
	}
	void init() {
		initButton(play, playWidth, playHeight, playX, playY, ButtonColor);
		initButton(exit, exitWidth, exitHeight, exitX, exitY, ButtonColor);
	}
	void initButton(Button &button, int width, int height, int x, int y, Color color) {
		button.Body.width = width;
		button.Body.height = height;
		button.Body.x = x;
		button.Body.y = y;
		button.Color = color;
	}
	void draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		drawButton(play);
		drawButton(exit);
		drawText();
		EndDrawing();
	}
	void update(){
		followMenuCursor(cursor);
		exitGame(cursor,exit);
		startGame(cursor,play,gameManager::Gamestate);
	}
	void input() {

	}
	void followMenuCursor(Cursor &cursor) {
		cursor.Position = GetMousePosition();
	}
	void drawText() {
		DrawText("Arkanoid", GetScreenWidth() / 2- 40, 30, 20, RAYWHITE);
		DrawText("Presiona 'Play' cuando estes listo para jugar.", GetScreenWidth() / 2 - GetScreenWidth() / 4, 50, 20, RAYWHITE);
		DrawText("Play", static_cast<int>(play.Body.x) + static_cast<int>(play.Body.width) / 3, static_cast<int>(play.Body.y) + static_cast<int>(play.Body.height) / 3, 20, RAYWHITE);
		DrawText("Exit", static_cast<int>(exit.Body.x) + static_cast<int>(exit.Body.width) / 3, static_cast<int>(exit.Body.y) + static_cast<int>(exit.Body.height) / 3, 20, RAYWHITE);
	}
	void drawButton(Button button) {
		DrawRectangleRec(button.Body,button.Color);
	}
	void exitGame(Cursor cursor, Button button) {
		if (buttonIsClicked(cursor, button)) {
			gameManager::gameIsOn = false;
		}
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
	void startGame(Cursor cursor, Button button, gameManager::Gamestates &gamestate) {
		if (buttonIsClicked(cursor, button)) {
			gamestate = FirstLevel;
		}
	}
}
