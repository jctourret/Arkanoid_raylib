#include "Player.h"
Player player;
const Color playerColor = GRAY;
const int playerX= GetScreenWidth() / 2;
const int playerY= GetScreenHeight() - GetScreenHeight() / 10;
const int playerWidth = 75;
const int playerHeight = 10;
const int playerSpeed = 8;
const int playerLives = 5;
void PlayerF::init(Player player,int width,int height, int x, int y,int lives,int speed,Color color) {
	player.Body.width=width	;
	player.Body.height=height;
	player.Body.x=x;
	player.Body.y=y;
	player.Speed = speed;
	player.Lives = lives;
	player.Color=color;
}
