#include "Objects\Window.h"
namespace window {
	const int screenWidth = 800;
	const int screenHeight = 450;
	void init() {
		InitWindow(screenWidth, screenHeight, "Arkanoid");
	}
}