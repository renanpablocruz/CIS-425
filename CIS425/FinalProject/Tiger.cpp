#include "Tank.h"
#include "Tiger.h"

Tiger::Tiger(elem t) : Tank(5, 5, 7, 3, 3, t){}

void Tiger::draw(int pos[], double size)
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}

void Tiger::shoot()
{
	glBegin(GL_LINE_STRIP);
	glEnd();
}
