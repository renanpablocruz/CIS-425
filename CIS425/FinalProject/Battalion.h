#ifndef BATTALION_H
#define BATTALION_H

#include "Tank.h"
#include "Panzer.h"
#include "Panther.h"
#include "Tiger.h"
#include <vector>

enum battalionState{INACTIVE, ATTACKING, DEFENDING};

class Battalion
{
private:
	std::vector<Tank*> tanks;
	int selectedTank;
public:
	Battalion();
	Battalion(int value);
	void computeDamage(int damage, elem bulletType);
	void draw(battalionState state);
	Bullet* getBullet();
	void getPosOfTank(unsigned int ind, float &_x, float &_y, float &_z);
	void getPosOfSelectedTank(float &_x, float &_y, float &_z);
	int getSelectedTank();
	tankState getStateOfTank();
	std::vector<const Tank*> getAllTanks();
	bool hasAnySelectedTank();
	bool hasTanks();
	void moveTank(dir dr);
	int numTanks();
	void passTurn();
	void selectDefaultTank();
	void selectNextTank();
	void selectNoTank();
	void setTargetMode();
	void setWaitingMode();
	void shoot(float _x, float _y, float _z);
	void update(int dt);
};

#endif