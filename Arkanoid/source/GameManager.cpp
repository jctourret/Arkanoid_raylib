#include "GameManager.h"
#include "raylib.h"
#include "Menu.h"
#include "PowerUp.h"
#include "FirstLevel.h"
#include "End.h"
#include "Player.h"
#include "Ball.h"
#include "Bricks.h"
#include "Window.h"

using namespace powerup;
using namespace menu;
using namespace bricks;
using namespace players;
using namespace balls;

namespace gameManager{
	bool gameIsOn=true;
	Gamestates Gamestate=Menu;
	void init();
	void runGame() {
		gameManager::init();
		while (!WindowShouldClose() && gameIsOn) {
			switch (Gamestate){
			case Menu:
				menu::run();
				break;
			case FirstLevel:
				firstlv::run();
				break;
			case SecondLevel:
				break;
			case ThirdLevel:
				break;
			case End:
				end::run();
				break;
			}
		}
	}
	void init() {
		window::init();
		powerup::init();
		menu::init();
		end::init();
		players::init();
		balls::init();
		bricks::init();
	}
}
