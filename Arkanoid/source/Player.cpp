#include "Player.h"
#include "Window.h"
using namespace window;
namespace players {
	Player player;
	const Color playerColor = GRAY;
	const int playerWidth = 75;
	const int playerHeight = 10;
	const int playerX = screenWidth / 2 - playerWidth / 2;
	const int playerY = screenHeight - screenHeight / 10;
	const int playerSpeed = screenWidth;
	const int playerLives = 5;
	void initplayer(Player &player, int width, int height, int x, int y, int lives, int speed, Color color);
	void init(){
		initplayer(player, playerWidth, playerHeight, playerX, playerY, playerLives, playerSpeed, playerColor);
	}
	void initplayer(Player &player, int width, int height, int x, int y, int lives, int speed, Color color) {
		player.Body.width = width;
		player.Body.height = height;
		player.Body.x = x;
		player.Body.y = y;
		player.Speed = speed;
		player.Lives = lives;
		player.Color = color;
	}
}