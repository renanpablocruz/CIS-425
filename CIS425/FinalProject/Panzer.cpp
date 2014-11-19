#include "Tank.h"
#include "Panzer.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 2, 5, t){}

void Panzer::draw(int pos[], double size)
{
	glColor3f(1, 0, 0);
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidCube(8);
	glPopMatrix();
}

void Panzer::shoot()
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}
