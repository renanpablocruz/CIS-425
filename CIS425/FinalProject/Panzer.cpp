#include "Panzer.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 2, t){}

void Panzer::draw()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	if (getType() == FIRE) glBindTexture(GL_TEXTURE_2D, RED + 1);
	else if (getType() == EARTH) glBindTexture(GL_TEXTURE_2D, BROWN + 1);
	else if (getType() == WATER) glBindTexture(GL_TEXTURE_2D, BLUE + 1);
	glPushMatrix();
	glTranslatef(x + 0.5, y + 0.5, z + 0.5);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -0.5); // top
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, -0.5, -0.5); // down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5); // front
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -0.5); // back
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.5, 0.5); // right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5); // left
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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
