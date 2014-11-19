#ifndef PANZER_H
#define PANZER_H

#include "Tank.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

class Panzer : public Tank
{
public:
	Panzer();
	Panzer(elem t);
	void draw(int pos[]);
	void shoot();
};

#endif