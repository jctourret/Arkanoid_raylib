#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"

namespace bricks {
	struct Brick
	{
		Rectangle Body;
		bool active;
	};
	extern const int bricksPerLine;
	extern const int linesOfBricks;
	extern const int brickWidth;
	extern const int brickHeigth;
	extern Brick brick[][20];
	void init(Brick brick, int width, int heigth);
}
#endif BRICKS_H