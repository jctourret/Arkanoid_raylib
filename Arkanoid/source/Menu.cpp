#include "Menu.h"
Cursor cursor;
Rectangle playButton;
Rectangle exitButton;
const int playButtonWidth = 100;
const int playButtonHeight = 50;
const int playButtonY = GetScreenHeight() / playButtonHeight * 4;
const int playButtonX = GetScreenWidth() - playButtonWidth/2;
const int exitButtonWidth = 100;
const int exitButtonHeight = 50;
const int exitButtonY = GetScreenHeight() / 2- exitButtonHeight*4;
const int exitButtonX = GetScreenWidth() - exitButtonWidth / 2;
void MenuF::run(){

}
void MenuF::initButton(Rectangle button,int width, int height, int x, int y) {
	button.width = width;
	button.height = height;
	button.x = x;
	button.y = y;
}