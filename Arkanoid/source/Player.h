#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
struct Player {
	Rectangle Body;
	Color Color;
	int Lives;
	int Speed;
};
extern Player player;
extern const Color playerColor = GRAY;
extern const int playerX = GetScreenWidth() / 2;
extern const int playerY = GetScreenHeight() - GetScreenHeight() / 10;
extern const int playerWidth = 75;
extern const int playerHeight = 10;
extern const int playerSpeed = 8;
extern const int playerLives = 5;
namespace PlayerF {
	void init(Player player, int width, int height, int x, int y,int lives,int speed, Color color);
}
#endif PLAYER_H
