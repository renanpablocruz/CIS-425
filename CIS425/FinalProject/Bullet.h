#ifndef BULLET_H
#define BULLET_H

#include "Utils.h"

class Bullet
{
protected:
	elem type;
	float x;
	float y;
	float z;
	int damage;
	float radius;
	float height;
	dir direction;
public:
	Bullet();
	Bullet(elem t, float _x, float _y, float _z, int dmg, float r, float h, dir dr);
	~Bullet();
	virtual void draw() = 0;
};

#endif