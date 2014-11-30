#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Battalion.h"

class Game
{
private:
	std::vector<Battalion*> battalions;
	int activeBattalion;
	int targetBattalion;
public:
	Game();
	void animate();
	void drawTerrain();
	void draw();
	void getPosOfTheCurrentTank(float &x, float &y, float &z);
	void getPosOfSelectedTank(int player, float &x, float &y, float &z);
	void getPosOfTank(int player, int indOfTank, float &x, float &y, float &z);
	tankState getStateOfTank(int player);
	bool hasAnySelectedTank(int player);
	bool hasTanks(int player);
	void moveTank(int player, dir direction);
	void newTurn();
	void selectDefaultTank(int player);
	void selectNextTank(int player);
	void setTargetMode(int player);
	void setWaitingMode(int player);
	void shoot(int player, int _x, int _y, int _z);
	void shoot2(int tankAtt, int tankDef);
};

#endif