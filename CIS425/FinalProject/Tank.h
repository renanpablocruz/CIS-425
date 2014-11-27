#ifndef TANK_H
#define TANK_H

#include "Bullet.h"
#include "Utils.h"

enum tankState {WAITING, MOVING, SELECTING_TARGET, SHOOTING, INVALID_TANK};

class Tank
{
protected:
	elem type;
	int range;
	int max_life;
	int life;
	int max_ammo;
	int ammo;
	int max_mov;
	int mov;
	Bullet* bullet;
	float x, y, z;
	float xf, yf, zf;
	dir orientation;
	tankState state;
	dir moveTo;
public:
	Tank();
	Tank(int ml, int r, int a, int ms, elem t);
	void animate(int value);
	bool canMov();
	bool canShoot(float x2, float y2, float z2);
	virtual void draw() = 0;
	void getFinalPos(float &_x, float &_y, float &_z);
	void getPos(float &_x, float &_y, float &_z);
	tankState getState();
	elem getType();
	void modLife(int d);
	void passTurn();
	void setMoveTo(dir dr);
	void setPos(float x, float y, float z);
	void setSelectTargetMode();
	void setWaitingMode();
	virtual void shoot(float _x, float _y, float _z) = 0;	
};

#endif
