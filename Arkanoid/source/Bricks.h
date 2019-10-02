#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"
struct Brick
{
	Rectangle Body;
	bool active;
};
extern const int bricksPerLine = 20;
extern const int linesOfBricks = 5;
extern const int brickWidth = GetScreenWidth() / bricksPerLine;
extern const int brickHeigth = GetScreenHeight() / 10;
extern Brick brick[linesOfBricks][bricksPerLine];
namespace BrickF {
	void init(Brick brick, int width, int heigth);
}
#endif BRICKS_H