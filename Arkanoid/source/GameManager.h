#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
enum Gamestates {
	Menu,
	Gameplay,
	End
};
extern bool gameIsOn;
extern Gamestates Gamestate;
void runGame();
#endif GAMEMANAGER_H
