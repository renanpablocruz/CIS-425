#include "Tank.h"
#include "Panzer.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 2, 5, t){}

void Panzer::draw(int pos[])
{
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(pos[0]+0.5, pos[1]+0.5, pos[2]+0.5);
	glutSolidCube(1);
	glPopMatrix();
}

void Panzer::shoot()
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}
