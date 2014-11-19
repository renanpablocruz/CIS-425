#include "Tank.h"
#include "Panther.h"

Panther::Panther(elem t) : Tank(12, 4, 10, 5, 2, t){}

void Panther::draw(int pos[])
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}

void Panther::shoot()
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}
