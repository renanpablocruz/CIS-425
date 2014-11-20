#ifndef TANK_H
#define TANK_H

#include "Bullet.h"
#include "Utils.h"

class Tank
{
private: // todo : do it protected
	elem type;
	int range;
	int max_life;
	int life;
	int max_ammo;
	int ammo;
	int max_mov;
	int mov;
	Bullet* bullet;
	float x;
	float y;
	float z;
	dir direction;
public:
	Tank();
	Tank(int ml, int r, int a, int ms, elem t);
	void modLife(int d);
	elem getType();
	void setPos(float x, float y, float z);
	void getPos(float &_x, float &_y, float &_z);
	void move(dir direction);
	bool canMov();
	void passTurn();
	virtual void draw() = 0;
	virtual void shoot() = 0;
};

#endif
