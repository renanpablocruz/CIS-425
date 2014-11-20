#include "Tank.h"
#include "Panzer.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 2, 5, t){}

void Panzer::draw()
{
	if(getType() == FIRE) glColor3f(1, 0, 0);
	else if (getType() == EARTH) glColor3f(0.6, 0.4, 0.2);
	else if (getType() == WATER) glColor3f(0, 0, 1);
	else glColor3f(0, 0, 0);
	glPushMatrix();
	float _x, _y, _z;
	getPos(_x, _y, _z);
	glTranslatef(_x+0.5, _y+0.5, _z+0.5);
	glutSolidCube(1);
	glPopMatrix();
}

void Panzer::shoot()
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}
