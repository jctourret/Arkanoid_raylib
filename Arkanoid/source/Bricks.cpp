#include "Bricks.h"
#include "Window.h"
using namespace window;
namespace bricks {
	const int brickWidth = screenWidth / 15;
	const int brickHeigth =screenHeight / 10;
	Brick brick;
	void initBrick(Brick &brick, int width, int heigth);
	void init() {
		initBrick(brick, brickWidth, brickHeigth);
	}
	void initBrick(Brick &brick, int width, int heigth) {
		brick.Body.width = width;
		brick.Body.height = heigth;
	}
}