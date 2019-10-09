#include "Bricks.h"
namespace bricks {
	const int brickWidth = GetScreenWidth() / 15;
	const int brickHeigth = GetScreenHeight() / 10;
	Brick brick;
	void initBrick(Brick brick, int width, int heigth);
	void init() {
		initBrick(brick, brickWidth, brickHeigth);
	}
	void initBrick(Brick brick, int width, int heigth) {
		brick.Body.width = width;
		brick.Body.height = heigth;
	}
}