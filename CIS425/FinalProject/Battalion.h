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
public:
	Battalion();
	Battalion(int value);
	void animate(int dt);
	bool anySelectedTank();
	int selectedTank();
	void draw();
	bool hasTanks();
	int numTanks();
	void selectTank(int ind);
	void deselectTank(int ind);
	void getPosOfTank(int ind, float &_x, float &_y, float &_z);
	tankState getStateOfTank();
	void setTargetModeOfSelectedTank();
	void shoot();
	void moveTank(dir dr);
	void newTurn();
};

#endif