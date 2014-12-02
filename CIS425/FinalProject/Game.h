#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Battalion.h"
#include "PantherBullet.h"
#include "PanzerBullet.h"
#include "TigerBullet.h"

class Game
{
private:
	std::vector<Battalion*> battalions;
	int activeBattalion;
	int targetBattalion;
	Bullet* bullet;
	bool createdBullet;
public:
	Game();
	bool activeBattalionHasAnySelectedTank();
	void computeDamage(int damage);
	bool currentPlayerHasAnySelectedTank();
	void draw();
	void drawBullet();
	void drawTerrain();
	void getBullet();
	void getPosOfTheCurrentTank(float &x, float &y, float &z);
	void getPosOfSelectedTank(int player, float &x, float &y, float &z);
	void getPosOfTank(int player, int indOfTank, float &x, float &y, float &z);
	tankState getStateOfCurrentTank();
	tankState getStateOfTank(int player);
	bool hasAnySelectedTank(int player);
	bool hasTanks(int player);
	bool isTheGameOver();
	void moveCurrentTank(dir direction);
	void moveTank(int player, dir direction);
	void newTurn();
	void selectDefaultTank(int player);
	void selectDefaultTankForTheCurrentTargetPlayer();
	void selectFocus();
	void selectNextTank(int player);
	void setCurrentTankToTargetMode();
	void setCurrentTankToWaitingMode();
	void setTargetMode(int player);
	void setWaitingMode(int player);
	void shoot();
	void update();
	void writeCongrats();
};

#endif