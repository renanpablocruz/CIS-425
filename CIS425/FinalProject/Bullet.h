#ifndef BULLET_H
#define BULLET_H

#include "Utils.h"

class Bullet
{
private:
	elem type;
	int x;
	int y;
	int z;
	int damage;
public:
	virtual void draw() = 0;
};

#endif