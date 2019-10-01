#ifndef MENU_H
#define MENU_H
#include "raylib.h"
struct Cursor{
	Vector2 Position;
	Color Color = WHITE;
	Vector2 Speed = { 7.5f,6.0f };
	int Radius = 10;
};
extern Cursor cursor;
extern Rectangle playButton;
extern Rectangle exitButton;
extern const int playButtonWidth;
extern const int playButtonHeight;
extern const int playButtonY;
extern const int playButtonX;
extern const int exitButtonWidth = 100;
extern const int exitButtonHeight = 50;
extern const int exitButtonY = GetScreenHeight() / 2 - exitButtonHeight * 4;
extern const int exitButtonX = GetScreenWidth() - exitButtonWidth / 2;
namespace MenuF {
	extern void run();
	extern void initButton(Rectangle button, int width, int height, int x, int y);
	
}
#endif MENU_H