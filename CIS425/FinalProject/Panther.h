#ifndef PANTHER_H
#define PANTHER_H

#include "Tank.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

class Panther : public Tank
{
public:
	Panther();
	Panther(elem t);
	void draw(int pos[]);
	void shoot();
};

#endif