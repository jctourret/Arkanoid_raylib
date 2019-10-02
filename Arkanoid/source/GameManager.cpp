#include "GameManager.h"
#include "raylib.h"
#include "Menu.h"
#include "End.h"
#include "Ball.h"
#include "Player.h"
#include "Bricks.h"
bool gameIsOn;
Gamestates Gamestate;
void runGame() {
	init();
	while (!WindowShouldClose() || gameIsOn) {
		switch (Gamestate)
		{
		case Menu:
			MenuF::run();
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
void init() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Arkanoid");
	BallF::init(ball, ballPosition);
	MenuF::initButton(playButton, playButtonWidth, playButtonHeight, playButtonX, playButtonY);
	MenuF::initButton(exitButton, exitButtonWidth, exitButtonHeight, exitButtonX, exitButtonY);
	PlayerF::init(player, playerWidth, playerHeight, playerX, playerY,playerLives,playerSpeed, playerColor);
	BrickF::init(brick[linesOfBricks][bricksPerLine], brickWidth, brickHeigth);
}