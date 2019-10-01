#include "GameManager.h"
#include "raylib.h"
#include "Menu.h"
#include "End.h"
#include "Ball.h"
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
		case Gameplay:
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
	BallF::initBall();
	MenuF::initButton(playButton, playButtonWidth, playButtonHeight, playButtonX, playButtonY);
	MenuF::initButton(exitButton, exitButtonWidth, exitButtonHeight, exitButtonX, exitButtonY);
}