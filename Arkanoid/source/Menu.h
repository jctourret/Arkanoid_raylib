#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "GameManager.h"
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
	extern Cursor cursor;
	extern Button play;
	extern Button exit;
	extern const int playWidth;
	extern const int playHeight;
	extern const int playY;
	extern const int playX;
	extern const int exitWidth;
	extern const int exitHeight;
	extern const int exitY;
	extern const int exitX;
	extern const Color ButtonColor;
	extern void run();
	extern void initButton(Button &button,int width, int height, int x, int y, Color color);
}
#endif MENU_H