#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
namespace players {
	struct Player {
		Rectangle Body;
		Color Color;
		int Lives;
		int Speed;
	};
	extern Player player;
	void init();
}
#endif PLAYER_H
