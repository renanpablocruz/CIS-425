#include "PanzerBullet.h"

PanzerBullet::PanzerBullet(elem t, float _x, float _y, float _z, float _xf, float _yf, float _zf, dir o) : Bullet(t, _x, _y, _z, _xf, _yf, _zf, 50, 0.2, 0.4, o){};//todo: fix 50 to 5

void PanzerBullet::draw()
{
	if (type == FIRE) glColor3f(1.0, 0.0, 0.4);
	else if (type == EARTH) glColor3f(0.4, 0.4, 0.0);
	else if (type == WATER) glColor3f(0.0, 0.6, 0.8);
	else glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(x + 0.5, y + 0.5, z + 0.5);
	if (orientation == RIGHT) glScalef(height, radius, radius);
	else if (orientation == RIGHT || orientation == LEFT) glScalef(height, radius, radius);
	else if (orientation == UP || orientation == DOWN) glScalef(radius, radius, height);
	else glScalef(0.1, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();
}
