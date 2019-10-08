#include "GameManager.h"
#include "raylib.h"
#include "Menu.h"
#include "End.h"
#include "Ball.h"
#include "Player.h"
#include "Bricks.h"
using namespace menu;
using namespace bricks;
using namespace players;
using namespace balls;

namespace gameManager{
	bool gameIsOn;
	const int screenWidth = 800;
	const int screenHeight = 450;
	Gamestates Gamestate;
	void init(){
		InitWindow(screenWidth, screenHeight, "Arkanoid");
		balls::init(ball, ballPosition);
		initButton(play, playWidth, playHeight, playX, playY,ButtonColor);
		initButton(exit, exitWidth, exitHeight, exitX, exitY, ButtonColor);
		init(player, playerWidth, playerHeight, playerX, playerY, playerLives, playerSpeed, playerColor);
		init(brick[linesOfBricks][bricksPerLine], brickWidth, brickHeigth);
	}
	void runGame() {
		gameManager::init();
		while (!WindowShouldClose() || gameIsOn) {
			switch (Gamestate)
			{
			case Menu:
				menu::run();
				break;
			case FirstLevel:
				break;
			case SecondLevel:
				break;
			case ThirdLevel:
				break;
			case End:
				break;
			}
		}
	}

}
