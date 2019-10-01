#include "Player.h"
Player player;
const Color playerColor = GRAY;
const int playerX= GetScreenWidth() / 2;
const int playerY= GetScreenHeight() - GetScreenHeight() / 10;
const int playerWidth = 75;
const int playerHeight = 10;
void PlayerF::initPlayer(Player player,int width,int height, int x, int y,Color color) {
	player.Body.width=width	;
	player.Body.height=height;
	player.Body.x=x;
	player.Body.y=y;
	player.Color=color;
}
