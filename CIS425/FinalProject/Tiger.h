#ifndef TIGER_H
#define TIGER_H

#include "Tank.h"
#include "glutInclude.h"


class Tiger : public Tank
{
public:
	Tiger();
	Tiger(elem t);
	void draw(int pos[]);
	void shoot();
};

#endif