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
	extern const Color playerColor;
	extern const int playerX;
	extern const int playerY;
	extern const int playerWidth;
	extern const int playerHeight;
	extern const int playerSpeed;
	extern const int playerLives;
	void init(Player player, int width, int height, int x, int y,int lives,int speed, Color color);
}
#endif PLAYER_H
