#include "PowerUp.h"
namespace powerup {
	PowerUp GrowPlayer;
	PowerUp Gun;
	PowerUp CatchBall;
	int powerUpWidth = 20;
	int powerUpHeight = 10;

	void initPowerUp(PowerUp &power);

	void init() {
		initPowerUp(GrowPlayer);
		initPowerUp(Gun);
		initPowerUp(CatchBall);
	}
	void initPowerUp(PowerUp &power) {
		power.Body.width = powerUpWidth;
		power.Body.height = powerUpHeight;
		power.Active = false;
		power.Bullet.width = powerUpHeight/2;
		power.Bullet.height = powerUpWidth/2;
	}
}