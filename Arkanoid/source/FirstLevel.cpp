#include "FirstLevel.h"
#include "Player.h"
#include "Bricks.h"
#include "Ball.h"
#include "Window.h"
using namespace players;
using namespace window;
namespace firstlv {
	void input();
	void update();
	void draw();
	void movePlayer(Player player);
	void run() {
		input();
		update();
		draw();
	}
	void input() {
		movePlayer(player);
	}
	void update() {

	}
	void draw() {
		BeginDrawing();
		EndDrawing();
	}
	void movePlayer(Player player) {
		if (IsKeyDown(KEY_LEFT)) player.Body.x -= player.Speed;
		if ((player.Body.x - player.Body.width) <= 0) player.Body.x = player.Body.width / 2;
		if (IsKeyDown(KEY_RIGHT)) player.Body.x += player.Speed;
		if ((player.Body.x + player.Body.width) >= screenWidth) player.Body.x = screenWidth - player.Body.width;
	}
}