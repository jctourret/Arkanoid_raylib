#include "Bricks.h"
namespace bricks {
	struct Brick{
		Rectangle Body;
		bool active;
	};
	const int bricksPerLine = 20;
	const int linesOfBricks = 5;
	const int brickWidth = GetScreenWidth() / bricksPerLine;
	const int brickHeigth = GetScreenHeight() / 10;
	Brick brick[linesOfBricks][bricksPerLine];
	void initBrick(Brick brick, int width, int heigth);
	void init() {
		initBrick(brick[linesOfBricks][bricksPerLine], brickWidth, brickHeigth);
	}
	void initBrick(Brick brick, int width, int heigth) {
		brick.Body.width = width;
		brick.Body.height = heigth;
	}
	void draw() {
		drawFirstlevel(brick[][bricksPerLine]);
	}
	void drawFirstlevel(Brick brick[][]){
		for (int i = 0; i < x; i++){
			for (int j = 0; j < bricksPerLine; j++){
				if (brick[i][j].active){
					if ((i + j) % 2 == 0) DrawRectangle(brick[i][j].Body.x,brick[i][j].Body.y, brick[i][j].Body.width, brick[i][j].Body.height, GRAY);
					else DrawRectangle(brick[i][j].Body.x, brick[i][j].Body.y, brick[i][j].Body.width, brick[i][j].Body.height, DARKGRAY);
				}
			}
		}
	}
}