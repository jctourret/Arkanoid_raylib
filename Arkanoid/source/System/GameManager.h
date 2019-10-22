#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
namespace gameManager {
	enum Gamestates {
		Menu,
		FirstLevel,
		SecondLevel,
		ThirdLevel,
		End
	};
	extern bool gameIsOn;
	extern Gamestates Gamestate;
	void runGame();
}
#endif GAMEMANAGER_H