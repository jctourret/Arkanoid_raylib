#include "raylib.h"
#include "System\GameManager.h"
#include "Scenes\Menu.h"
#include "Objects\PowerUp.h"
#include "Scenes\FirstLevel.h"
#include "Scenes\End.h"
#include "Objects\Player.h"
#include "Objects\Ball.h"
#include "Objects\Bricks.h"
#include "Objects\Window.h"

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
