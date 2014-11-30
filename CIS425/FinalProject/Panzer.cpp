#include "Utils.h"
#include "Tank.h"
#include "Panzer.h"
#include "PanzerBullet.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 2, t){}

void Panzer::draw()
{
	if(getType() == FIRE) glColor3f(1, 0, 0);
	else if (getType() == EARTH) glColor3f(0.6, 0.4, 0.2);
	else if (getType() == WATER) glColor3f(0, 0, 1);
	else glColor3f(0, 0, 0);
	glPushMatrix();	// tank
	glTranslatef(x + 0.5, y + 0.5, z + 0.5);
	glutSolidCube(1);
	glPopMatrix();
	if (bullet != NULL) bullet->draw(); // if exist, the bullet

}

void Panzer::shoot(float xf, float yf, float zf)
{
	if (canShoot(xf, yf, zf))
	{
		spendAmmo();
		orientation = getDirForTank(x, z, xf, zf);
		bullet = new PanzerBullet(type, x, y, z, xf, yf, zf, getDirForBullet(x, y, xf, yf));
		state = SHOOTING;
	}
}
