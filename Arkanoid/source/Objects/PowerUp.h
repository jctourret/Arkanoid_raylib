#ifndef POWERUP_H
#define POWERUP_H
#include "raylib.h"
namespace powerup {
	struct PowerUp {
		Rectangle Body;
		Color Color;
		bool Active;
		Rectangle Bullet;
		bool BulletActive;
	};
	extern PowerUp GrowPlayer;
	extern PowerUp Gun;
	extern PowerUp CatchBall;
	extern void init();
}
#endif // !POWERUP_H

