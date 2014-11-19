#ifndef TIGER_H
#define TIGER_H

#include "Tank.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

class Tiger : public Tank
{
public:
	Tiger();
	Tiger(elem t);
	void draw(int pos[]);
	void shoot();
};

#endif