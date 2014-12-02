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
	void computeDamage(int damage);
	void draw();
	void drawBullet();
	void drawTerrain();
	void getBullet();
	void getBullet2();
	void getPosOfTheCurrentTank(float &x, float &y, float &z);
	void getPosOfSelectedTank(int player, float &x, float &y, float &z);
	void getPosOfTank(int player, int indOfTank, float &x, float &y, float &z);
	tankState getStateOfTank(int player);
	bool hasAnySelectedTank(int player);
	bool hasTanks(int player);
	bool isTheGameOver();
	void moveTank(int player, dir direction);
	void newTurn();
	void selectDefaultTank(int player);
	void selectNextTank(int player);
	void setTargetMode(int player);
	void setWaitingMode(int player);
	void shoot();
	void update();
	void writeCongrats();
};

#endif