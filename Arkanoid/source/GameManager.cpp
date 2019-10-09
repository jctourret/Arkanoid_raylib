#include "GameManager.h"
#include "raylib.h"
#include "Menu.h"
#include "End.h"
#include "Ball.h"
#include "Player.h"
#include "Bricks.h"
#include "Window.h"
using namespace menu;
using namespace bricks;
using namespace players;
using namespace balls;
namespace gameManager{
	bool gameIsOn=true;
	Gamestates Gamestate;
	void init();
	void runGame() {
		gameManager::init();
		while (!WindowShouldClose() && gameIsOn) {
			switch (Gamestate){
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
	void init() {
		window::init();
		menu::init();
		balls::init();
		players::init();
		bricks::init();
	}
}
