#ifndef PANTHER_H
#define PANTHER_H

#include "Tank.h"
#include "glutInclude.h"

class Panther : public Tank
{
public:
	Panther();
	Panther(elem t);
	void draw(int pos[]);
	void shoot();
};

#endif