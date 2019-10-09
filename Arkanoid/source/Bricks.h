#ifndef BRICKS_H
#define BRICKS_H
#include "raylib.h"
namespace bricks {
	struct Brick {
		Rectangle Body;
		bool active;
	};
	extern Brick brick;
	void init();
}
#endif BRICKS_H