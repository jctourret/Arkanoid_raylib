#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
struct Player {
	Rectangle Body;
	Color Color;
	int Lives;
};
extern Player player;
namespace PlayerF {
	void initPlayer(Player player, int width, int height, int x, int y, Color color);
}
#endif PLAYER_H
