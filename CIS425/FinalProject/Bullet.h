#ifndef BULLET_H
#define BULLET_H

#include "Utils.h"

enum bulletState {FLYING, DONE};

class Bullet
{
protected:
	int damage;
	elem type;
	float x, y, z;
	float xf, yf, zf;
	float height;
	dir orientation;
	float radius;
	bulletState state;
public:
	Bullet();
	Bullet(elem t, float _x, float _y, float _z, float _xf, float _yf, float _zf, int dmg, float r, float h, dir dr);
	~Bullet(); // todo: need to implement?
	void animate();
	virtual void draw() = 0;
	bulletState getState();
};

#endif
