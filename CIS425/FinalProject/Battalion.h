#ifndef BATTALION_H
#define BATTALION_H

#include "Tank.h"
#include "Panzer.h"
#include "Panther.h"
#include "Tiger.h"
#include <vector>

class Battalion
{
private:
	std::vector<Tank*> tanks;
	int selectedTank;
public:
	Battalion();
	Battalion(int value);
	void animate(int dt);
	bool anySelectedTank();
	void draw();
	void getPosOfTank(int ind, float &_x, float &_y, float &_z);
	int getSelectedTank();
	tankState getStateOfTank();
	bool hasTanks();
	void moveTank(dir dr);
	void newTurn();
	int numTanks();
	void selectDefaultTank();
	void selectNextTank();
	void selectNoTank();
	void setTargetMode();
	void setWaitingMode();
	void shoot(float _x, float _y, float _z);
};

#endif