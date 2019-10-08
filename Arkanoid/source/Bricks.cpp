#include "Bricks.h"
namespace bricks {
	const int bricksPerLine = 20;
	const int linesOfBricks = 5;
	const int brickWidth = GetScreenWidth() / bricksPerLine;
	const int brickHeigth = GetScreenHeight() / 10;
	Brick brick[linesOfBricks][bricksPerLine];
	void init(Brick brick, int width, int heigth) {
		brick.Body.width = width;
		brick.Body.height = heigth;
	}
}