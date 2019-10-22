#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"
namespace bricks {
	struct Brick {
		Rectangle Body;
		bool Active;
		Color Color;
		int Lives;
		bool Powerup;
	};
	extern Brick brick;
	void init();
}
#endif BRICKS_H