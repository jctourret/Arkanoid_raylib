#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"
struct Brick
{
	Vector2 position;
	bool active;
};
extern const int bricksPerLine = 20;
extern const int linesOfBricks = 5;
extern Brick brick[linesOfBricks][bricksPerLine];
namespace Bricks {
	
}
#endif BRICKS_H