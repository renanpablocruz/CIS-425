#ifndef TANK_H
#define TANK_H

#include "Bullet.h"
#include "Utils.h"

enum tankState {WAITING, MOVING, SELECTING_TARGET, SHOOTING};

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
	bool selection;
public:
	Tank();
	Tank(int ml, int r, int a, int ms, elem t);
	void modLife(int d);
	elem getType();
	void setPos(float x, float y, float z);
	void getPos(float &_x, float &_y, float &_z);
	void getFinalPos(float &_x, float &_y, float &_z);
	bool canMov();
	void passTurn();
	virtual void draw() = 0;
	virtual void shoot() = 0;
	void animate(int value);
	void setMoveTo(dir dr);
	tankState getState();
	void setSelectTargetMode();
	void select();
	void deselect();
	bool isSelected();
};

#endif
